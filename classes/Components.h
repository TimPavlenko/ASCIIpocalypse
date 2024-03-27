class Component{
public:
    virtual void tick();
};

class CompPlayer : public Component{
public:
    void tick();
};
