#ifndef RobatzModule_h
#define RobatzModule_h

class RobatzModule {
  public:
    virtual boolean update(byte data);
    virtual void loop();
};

#endif
