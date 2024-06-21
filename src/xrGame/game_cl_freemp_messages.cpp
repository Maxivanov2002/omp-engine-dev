#include "stdafx.h"
#include "game_cl_freemp.h"
#include "UIGameFMP.h"
#include "ui/UIActorMenu.h"
#include "GameCraft.h"

void game_cl_freemp::TranslateGameMessage(u32 msg, NET_Packet& P)
{
	switch (msg)
	{
	case GAME_EVENT_MP_REPAIR_SUCCESS:
		{
			if (m_game_ui &&
				m_game_ui->ActorMenu().IsShown() &&
				m_game_ui->ActorMenu().GetMenuMode() == mmUpgrade
				)
			{
				u16 itemId = P.r_u16();

				PIItem item = smart_cast<PIItem>(Level().Objects.net_Find(itemId));
				if (item)
				{
					m_game_ui->ActorMenu().OnSuccessRepairMP(item);
				}
			}
		}break;
	case GAME_EVENT_MP_INSTALL_UPGRADE_SUCCESS:
		{
			if (m_game_ui &&
				m_game_ui->ActorMenu().IsShown() &&
				m_game_ui->ActorMenu().GetMenuMode() == mmUpgrade
				)
			{
				u16 itemId = P.r_u16();

				PIItem item = smart_cast<PIItem>(Level().Objects.net_Find(itemId));
				if (item)
				{
					m_game_ui->ActorMenu().OnSuccessUpgradeInstallMP(item);
				}
			}
		}break;
	case GE_CRAFT_ITEM:
	{
		if (!g_dedicated_server)
		{
			CUIGameFMP* fmp = smart_cast<CUIGameFMP*>(m_game_ui);
			fmp->getCraftMenu()->ReciveResult(P);
		}
	}
	break;
	default:
		inherited::TranslateGameMessage(msg, P);
	};
}
