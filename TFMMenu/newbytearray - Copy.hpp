#include <windows.h>
#include <iostream>
#include <cstring>
#include <vector>

class NewByteArray {
private:
	char* _buffer;
	int _length;
	int _position;
	void MemcpyOffset(char* dst, char* src, int size, int offset);
	void ResizeBuffer(int length);
	void Read(char* b, int off, int len);

public:
	NewByteArray(char* buf, int len);
	NewByteArray(int len);
	NewByteArray();
	~NewByteArray();
	int Read();
	void Write(int value);
	void WriteByte(int value);
	void WriteShort(int value);
	void WriteUTF(char* value);
	void WriteUTF(const char* value);
	void WriteBytes(char* value, int len);
	void WriteByte(int value, int position);
	void WriteShort(int value, int position);
	int GetLength();
	int ReadInt();;
	char ReadByte();
	short ReadShort();
	char* GetData(bool resize);
	std::string ReadUTF();
	
};