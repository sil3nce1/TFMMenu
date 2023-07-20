#include "newbytearray.hpp"


NewByteArray::NewByteArray(char* buf, int len)
{
	_buffer = new char[len];
	_length = len;
    _position = 0;
	memcpy(_buffer, buf, len);
}

NewByteArray::NewByteArray()
{
	_length = 1;
	_buffer = new char[_length];
	_position = 0;
}

void NewByteArray::MemcpyOffset(char* dst, char* src, int size, int offset)
{
	const char* src_offset = src + offset;
	char* dest_offset = dst + offset;
	memcpy(dest_offset, src_offset, size);
}

void NewByteArray::ResizeBuffer(int length)
{
	char* tempBuffer = new char[length];
	memcpy(tempBuffer, _buffer, _length);
	_buffer = new char[length];
	memcpy(_buffer, tempBuffer, _length);
	_length = length;
	delete[] tempBuffer;
}

NewByteArray::~NewByteArray()
{
	delete[] _buffer;
}


int NewByteArray::Read()
{
    if (_position >= _length) {
        return -1; 
    }

	int value = _buffer[_position] & 0xFF;
	_position++;
    return value;
}

void NewByteArray::Write(int value)
{
	_position += 1;
	if (_position > _length)
		ResizeBuffer(_position);

	_buffer[_position - 1] = (char)value;
}

char* NewByteArray::GetData(bool resize)
{
	if (resize)
		ResizeBuffer(_position);

	return _buffer;
}

int NewByteArray::GetLength()
{
	return _length;
}

void NewByteArray::WriteBytes(char* value, int len)
{
	int oldLength = _length;
	ResizeBuffer(_length + len);
	memcpy(_buffer + oldLength, value, len);
	_position = _length;
}

void NewByteArray::WriteByte(int value, int position)
{
	_buffer[position] = (char)value;
}

void NewByteArray::WriteShort(int value, int position)
{
	_buffer[position] = (value >> 8) & 0xFF;
	_buffer[position + 1] = value & 0xFF;
}

void NewByteArray::WriteUTF(const char* value)
{
	WriteUTF((char*)value);
}

void NewByteArray::WriteShort(int value)
{
	Write((value >> 8) & 0xFF);
	Write(value & 0xFF);
}

void NewByteArray::WriteByte(int value)
{
	Write(value);
}

void NewByteArray::WriteUTF(char* value)
{
	int len = strlen(value);
	WriteShort(len);

	for (int i = 0; i < len; i++)
	{
		WriteByte(value[i]);
	}
}

char NewByteArray::ReadByte()
{
	return (char)Read();
}

int NewByteArray::ReadInt()
{
	return (Read() << 24) | (Read() << 16) | (Read() << 8) | Read();
}

short NewByteArray::ReadShort()
{
	return (short)((Read() << 8) | Read());
}

std::string NewByteArray::ReadUTF()
{
    int size = (int)ReadShort();
    char* bytes = new char[size];
    for (int i = 0; i < size; i++) {
		int c = ReadByte();
		bytes[i] = c;
    }

	std::string s(bytes, size);

    delete[] bytes;
    return s;

}