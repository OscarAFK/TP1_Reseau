
class Serializer 
{
public:
	Serializer();
	Serializer(int size);
	~Serializer();

	template <typename T>
	void Serialize(T& val) {
		
		OutputStream stream;
		val.Write(stream);

		m_container = reinterpret_cast<char*>(stream.Data().data());
		m_sizeContainer = stream.Data().size_bytes();
	}

	//getter
	const char * getContainer();
	const int getSizeContainer();

private:

	char* m_container;
	int m_sizeContainer;
};