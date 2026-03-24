static int print_log(const char* log, size_t len, slog_flag_t flags, void* ctx) {
    fprintf(stderr, "%.*s", (int)len, log);
    return 0;
}

int main(int argc, char** argv) {
    slog_init(argv[0], SLOG_FLAGS_ALL, 0);
   
    slog_config_t cfg;
    slog_config_get(&cfg);
    cfg.nFlush = 1;
    cfg.logCallback = print_log;
    slog_config_set(&cfg);

    MU_RUN_SUITE(test_suite);
    MU_REPORT();

    return MU_EXIT_CODE;
}


