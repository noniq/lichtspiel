#ifndef EFFECT_PLUGS_H
#define EFFECT_PLUGS_H

class EffectPlugs {
  public:
    EffectPlugs(uint8_t _num, const uint8_t *_pins);
    void setup();
    uint8_t pluggedConnection();

  private:
    uint8_t num;
    const uint8_t *pins;
};

#endif
