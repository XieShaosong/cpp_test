#include <iostream>
using namespace std;

typedef struct
{
        std::string type;
        std::string code;
}Event;

typedef void (*eventCallback)(const Event *event, void *arg);

class CallBack
{
public:
	void registerEventCallback(eventCallback callback, void *arg)
	{
		eventCb = callback;
		eventArg = arg;
	}
	void test ()
	{
		Event event;
		event.type = "info";
		event.code = "start";
		eventCb(&event, eventArg);
	}
private:
	static eventCallback eventCb;
	static void *eventArg;
};

class Demo
{
public:
	static void realTimeEventCallback(const Event *event, void *arg)
	{
		Demo *demo = (Demo *)arg;
		demo->showA();
		cout << event->type << " " << event->code << endl;
	}
	void showA()
	{
		cout << a << endl;
	}
public:
	int a;
};

eventCallback CallBack::eventCb;
void *CallBack::eventArg;

int main()
{
	Demo demo_1;
	demo_1.a = 22;
	
	CallBack cb;
	cb.registerEventCallback(Demo::realTimeEventCallback, (void *)&demo_1);
	cb.test();
	
	return 0;
}

