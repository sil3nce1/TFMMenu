#include "bytearray.hpp"


ByteArray::ByteArray(char* buf, int len)
{
    _position = 0;
	_modified = false;
	for (int i = 0; i < len; i++)
	{
		_buffer.push_back((char)buf[i]);
	}
}

ByteArray::ByteArray(char* buf, int len, bool modified)
{
	_position = 0;
	_modified = modified;
	for (int i = 0; i < len; i++)
	{
		_buffer.push_back((char)buf[i]);
	}
}

ByteArray::ByteArray()
{
	_position = 0;
	_modified = false;
}


int ByteArray::read()
{
    if (_position >= _buffer.size())
        return -1;

	int value = _buffer[_position] & 0xFF;
	_position++;
    return value;
}

bool ByteArray::isModified()
{
	return _modified;
}

void ByteArray::write(int value)
{
	_buffer.push_back((char)value);
	_position += 1;
	_modified = true;
}

char* ByteArray::getData()
{
	return reinterpret_cast<char*>(_buffer.data());
}

int ByteArray::getLength()
{
	return _buffer.size();
}

void ByteArray::writeBytes(char* value, int len)
{
	for (int i = 0; i < len; i++)
	{
		_buffer.push_back((char)value[i]);
	}

	_position = _buffer.size();
}

void ByteArray::writeByte(int value, int position)
{
	_buffer[position] = (char)value;
}

void ByteArray::writeShort(int value, int position)
{
	_buffer[position] = (value >> 8) & 0xFF;
	_buffer[position + 1] = value & 0xFF;
}

void ByteArray::writeUTF(const char* value)
{
	writeUTF((char*)value);
}

void ByteArray::writeShort(int value)
{
	write((value >> 8) & 0xFF);
	write(value & 0xFF);
}

void ByteArray::writeByte(int value)
{
	write(value);
}

void ByteArray::writeUTF(char* value)
{
	int strLen = strlen(value);
	int utflen = 0;

	for (int i = 0; i < strLen; i++) {
		int c = value[i];
		if ((c >= 0x0001) && (c <= 0x007F)) {
			utflen++;
		}
		else if (c > 0x07FF) {
			utflen += 3;
		}
		else {
			utflen += 2;
		}
	}

	writeShort(utflen);
	int bytesCount = 0;
	char* tempBuffer = new char[utflen];

	for (int i = 0; i < strLen; i++) {
		int c = value[i];
		if ((c >= 0x0001) && (c <= 0x007F)) {
			tempBuffer[bytesCount++] = (char)c;
		}
		else if (c > 0x07FF) {
			tempBuffer[bytesCount++] = (char)(0xE0 | ((c >> 12) & 0x0F));
			tempBuffer[bytesCount++] = (char)(0x80 | ((c >> 6) & 0x3F));
			tempBuffer[bytesCount++] = (char)(0x80 | (c & 0x3F));
		}
		else {
			tempBuffer[bytesCount++] = (char)(0xC0 | ((c >> 6) & 0x1F));
			tempBuffer[bytesCount++] = (char)(0x80 | (c & 0x3F));
		}

	}

	writeBytes(tempBuffer, utflen);
	delete[] tempBuffer;
}

char ByteArray::readByte()
{
	return (char)read();
}

void ByteArray::writeIdentifier(const int identifier[])
{
	writeByte(identifier[0]);
	writeByte(identifier[1]);
}

char ByteArray::readByte(int position)
{
	int lastPosition = _position;
	char value = readByte();
	_position = lastPosition;
	return value;
}

bool ByteArray::readBoolean()
{
	return (read() != 0);
}

void ByteArray::setPosition(int position)
{
	_position = position;
}

int ByteArray::readInt()
{
	return (read() << 24) | (read() << 16) | (read() << 8) | read();
}

short ByteArray::readShort()
{
	return (short)((read() << 8) | read());
}

void ByteArray::writeInt(int value)
{
	_buffer.push_back((value >> 24) & 0xFF);
	_buffer.push_back((value >> 16) & 0xFF);
	_buffer.push_back((value >> 8) & 0xFF);
	_buffer.push_back(value & 0xFF);
}

std::string ByteArray::readUTF()
{
    int size = (int)readShort();
    char* bytes = new char[size];
    for (int i = 0; i < size; i++) {
		int c = readByte();
		bytes[i] = c;
    }

	std::string s(bytes, size);

    delete[] bytes;
    return s;

}