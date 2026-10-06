unsigned int inverteOrdemBytes(unsigned int i){
    unsigned int r;
    r = ((i & 0x000000FF) << 24) |
        ((i & 0x0000FF00) << 8) |
        ((i & 0x00FF0000) >> 8) |
        ((i & 0xFF000000) >> 8);
    return r;
}