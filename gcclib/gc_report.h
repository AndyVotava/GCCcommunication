struct __attribute__((packed)) gc_report {
    public:
    uint8_t SYXBA;
    uint8_t LRZD;
    uint8_t xStick;
    uint8_t yStick;
    uint8_t cxStick;
    uint8_t cyStick;
    uint8_t analogL;
    uint8_t analogR;
};