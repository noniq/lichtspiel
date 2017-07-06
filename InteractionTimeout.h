#ifndef INTERACTION_TIMEOUT_H
#define INTERACTION_TIMEOUT_H

class InteractionTimeout {
  public:
    InteractionTimeout(uint16_t _seconds);
    void reset();
    boolean timedOut();

  private:
    uint32_t lastInteractionMillis;
    uint16_t timeoutSeconds;
};

#endif
