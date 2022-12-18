#include "Font.h"
#include "DebugManager.h"

class ChatBox : public Object, public UIMesh
{
public:
	ChatBox();
	~ChatBox();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

private:
	struct Massage {
		Timer time;
		Font log;
	};
	Massage massage[5];
	int count;
	int maxChat;
};
