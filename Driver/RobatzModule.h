#ifndef RobatzModule_h
#define RobatzModule_h

class RobatzModule {
  public:
    virtual void update(byte data);
    virtual boolean loop();
    virtual int32_t outData();
    virtual byte answerSize();
};

#endif
