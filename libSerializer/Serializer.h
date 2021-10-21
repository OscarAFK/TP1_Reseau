#include <vector>

class Serializer 
{
public:
	Serializer();
	Serializer(int size);
	~Serializer() = default;

	template <typename T, std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<T>>>* = nullptr>
	void Serialize(T& val) {
		unsigned sizeOfVal = sizeof(val) / sizeof(T);

		m_container.resize(m_container.size() + sizeOfVal );
		
		memcpy(m_container.data() + m_posContainer, &val, sizeOfVal * sizeof(T));
		m_posContainer += sizeOfVal;

	}


	//getter
	const std::vector<char> getContainer();

private:


	std::vector<char> m_container;
	int m_posContainer;
};
