#include "Packet.h"
#include "ReceiveEntity.h"

void PacketProcessing(sf::Packet& packet)
{
	float x,y,rotation,rotation2;
	int num;
	sf::String name,name_type,name_type2, control;
	sf::Uint32 size;
	packet >> size;
	for (sf::Uint32 i = 0; i < size; ++i)
	{
		packet >> name;
		if(name=="Enemy" || name=="Player")
		{
			packet >> x >> y >> name_type >> name_type2 >> rotation >> rotation2;
			entities3.push_back(new ReceiveEntity(x, y, name_type, name_type2, rotation, rotation2));
		}else if(name=="Explosion")
		{
			packet >> x >> y >> num;
			entities3.push_back(new ReceiveEntity(x, y, num));
		}else
		{
			packet >> x >> y >> name_type >> rotation;
			entities3.push_back(new ReceiveEntity (x, y, name_type, rotation));
		}
	}
}