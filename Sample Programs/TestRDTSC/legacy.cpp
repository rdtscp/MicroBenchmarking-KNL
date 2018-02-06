std::cerr << "\n\n\n\n --- Markdown Table ---\n\n";
std::cerr << "\nLAT | O/Head | L1 Load | L2 Load | Mem Load | DIV(29-42) | PAUSE(25)";
std::cerr << "\n--- | --- | --- | --- | --- | --- | ---";
for (int i=0; i < 500; i++) {
    double oh_perc      = (double)ohead_lat[i] / (double)10;
    double l1_perc      = (double)l1_lat[i]    / (double)10;
    double l2_perc      = (double)l2_lat[i]    / (double)10;
    double mem_perc     = (double)mem_lat[i]   / (double)10;
    double div_perc     = (double)div_lat[i]   / (double)10;
    double pse_perc     = (double)pause_lat[i] / (double)10;
    if (i >= 500) {
        oh_perc = 0; l1_perc = 0; l2_perc = 0; div_perc = 0; pse_perc = 0;
    }
    std::string cycles;
    if (oh_perc > 1 || l1_perc > 1 || l2_perc > 1 || mem_perc > 1 || div_perc > 1 || pse_perc > 1) {
        int temp, digits;
        // STD::CERR
        std::cerr << "\n" << i;
        std::cerr << " | " << ohead_lat[i];
        if (oh_perc > 1) fprintf(stderr, "(%.2f%%)", oh_perc);
        std::cerr << " | " << l1_lat[i];
        if (l1_perc > 1) fprintf(stderr, "(%.2f%%)", l1_perc);
        std::cerr << " | " << l2_lat[i];
        if (l2_perc > 1) fprintf(stderr, "(%.2f%%)", l2_perc);
        std::cerr << " | " << mem_lat[i];
        if (mem_perc > 1) fprintf(stderr, "(%.2f%%)", mem_perc);
        std::cerr << " | " << div_lat[i];
        if (div_perc > 1) fprintf(stderr, "(%.2f%%)", div_perc);
        std::cerr << " | " << pause_lat[i];
        if (pse_perc > 1) fprintf(stderr, "(%.2f%%)", pse_perc);
    }
}