#include "Constants.h"

const FName Constants::ItemTypeToName(EITEM_TYPE itemtype)
{
	switch (itemtype)
	{
		case EITEM_TYPE::EQUIPMENT:
			return FName(TEXT("장비 아이템"));
		case EITEM_TYPE::EQUIPMENT_HELMET:
			return FName(TEXT("머리장식"));
		case EITEM_TYPE::EQUIPMENT_UPPER:
			return FName(TEXT("상의"));
		case EITEM_TYPE::EQUIPMENT_LOWER:
			return FName(TEXT("하의"));
		case EITEM_TYPE::EQUIPMENT_SHOES:
			return FName(TEXT("신발"));
		case EITEM_TYPE::WEAPON:
			return FName(TEXT("무기 아이템"));
		case EITEM_TYPE::WEAPON_SWORD:
			return FName(TEXT("한손검"));
		case EITEM_TYPE::WEAPON_MACE:
			return FName(TEXT("둔기"));
		case EITEM_TYPE::WEAPON_BOW:
			return FName(TEXT("활"));
		case EITEM_TYPE::USE:
			return FName(TEXT("소비 아이템"));
		case EITEM_TYPE::ETC:
			return FName(TEXT("기타 아이템"));
		case EITEM_TYPE::ETC_QUEST:
			return FName(TEXT("퀘스트 아이템"));
		default:
			return FName();
	}
}
