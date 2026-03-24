#!/usr/bin/env python3
import json
import sys
import subprocess

from argparse import ArgumentParser
from dataclasses import dataclass
from pathlib import Path

@dataclass
class GithubDependency:
    remote: str
    commit: str
    
    def to_dict(self) -> dict[str, str]:
        return { "remote": self.remote, "commit": self.commit }

    def from_dict(data) -> 'GithubDependency':
        return GithubDependency(remote = data["remote"], commit = data["commit"])

class HttpFileDependency:
    url: str
    sha256: str


type Dependency = GithubDependency | HttpFileDependency
type Dependencies = dict[str, Dependency]

external = Path("external")
bsl_deps = Path("bsl-deps.json")

def load_json(p: Path):
    with open(p) as f:
        return json.load(f)

def add_github_dependency(remote: str):
    group, repo = remote.split("/", 1)
    group_path = external / "github" / group

    group_path.mkdir(parents = True, exist_ok = True)

    subprocess.run(
            ["git", "clone", f"https://github.com/{remote}"], 
            cwd = group_path, 
            check = True,
    )

    res = subprocess.run(
            ["git", "rev-parse", "HEAD"], 
            cwd = group_path / repo, 
            check = True, 
            capture_output = True, 
            text = True,
    )

    return GithubDependency(
            remote = f"{group}/{repo}",
            commit = res.stdout.rstrip("\n"),
    )

def add(item: str):
    if item.startswith("github:"):
        dep = add_github_dependency(item.removeprefix("github:"))
    else:
        print(f"Invalid dependency: {item}", file=sys.stderr)
        exit(1)

    deps = load_json(bsl_deps) if bsl_deps.exists() else {}

    deps[item] = dep.to_dict()

    with open(bsl_deps, "w") as f:
        json.dump(deps, f)

def install_github_dep(dep: GithubDependency):
    group, repo = dep.remote.split("/", 1)
    group_path = external / "github" / group

    if (group_path / repo).exists():
        return

    group_path.mkdir(parents = True, exist_ok = True)

    subprocess.run(
            ["git", "clone", f"--revision={dep.commit}", "--depth=1", f"https://github.com/{dep.remote}"],
            check = True,
            capture_output = True,
            cwd = group_path,
    )

def install():
    if not bsl_deps.exists():
        print("Nothing to install", file = sys.stderr)

    deps = load_json(bsl_deps)

    for key, value in deps.items():
        if key.startswith("github:"):
            install_github_dep(GithubDependency.from_dict(value))
        else:
            print(f"Unknown dependency: {value}", file = sys.stderr)
            exit(1)
def main():
    parser = ArgumentParser(description = "Bespoke build tool")

    subcommands = parser.add_subparsers(dest = "command")

    add_parser = subcommands.add_parser("add", help = "Adds a dependency")
    add_parser.add_argument("item", help = "The item to add (ex: github:ffortier/test)")
    
    args = parser.parse_args()

    if args.command == "add":
        add(args.item)
    else:
        install()

if __name__ == "__main__":
    main()
