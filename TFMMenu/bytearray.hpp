#include <windows.h>
#include <iostream>
#include <cstring>
#include <vector>

class ByteArray {
private:
	std::vector<unsigned char> _buffer;
	int _position;
	bool _modified;

public:
	ByteArray(char* buf, int len);
	ByteArray(char* buf, int len, bool modified);
	ByteArray();
	void setPosition(int position);
	int read();
	char readByte(int position);
	void write(int value);
	void writeByte(int value);
	void writeShort(int value);
	void writeIdentifier(const int identifier[]);
	void writeUTF(char* value);
	void writeUTF(const char* value);
	void writeBytes(char* value, int len);
	void writeByte(int value, int position);
	void writeShort(int value, int position);
	void writeInt(int value);
	int getLength();
	int readInt();
	bool readBoolean();
	bool isModified();
	char readByte();
	short readShort();
	char* getData();
	std::string readUTF();
	
};