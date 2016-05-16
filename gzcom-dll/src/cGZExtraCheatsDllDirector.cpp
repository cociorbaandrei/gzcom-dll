#include "../include/cIGZApp.h"
#include "../include/cIGZFrameWork.h"
#include "../include/cISC4App.h"
#include "../include/cRZCOMDllDirector.h"
#include <stdio.h>
#include <Windows.h>

static const uint32_t kExtraCheatsPluginCOMDirectorID = 0x8bbd9623;
static const uint32_t kGZIID_cISC4App = 0x26ce01c0;

class cSC4ExtraCheatsPluginCOMDirector : public cRZCOMDllDirector
{
	public:
		uint32_t GetDirectorID() const {
			return kExtraCheatsPluginCOMDirectorID;
		}

		bool PreAppInit() {
			cIGZFrameWork* const pFramework = RZGetFrameWork();
			if (pFramework) {
				cIGZApp* const pApp = pFramework->Application();
				if (pApp) {
					cISC4App* pISC4App;
					if (pApp->QueryInterface(kGZIID_cISC4App, (void**)&pISC4App)) {
						MessageBoxA(NULL, "o shit waddup!", NULL, MB_OK);

						char test[64];
						sprintf_s(test, "%08X", pISC4App);
						MessageBoxA(NULL, test, NULL, MB_OK);

						sprintf_s(test, "%d", pISC4App->GetDebugFunctionalityEnabled());
						MessageBoxA(NULL, test, NULL, MB_OK);

						pISC4App->SetDebugFunctionalityEnabled(true);
					}
					else {
						MessageBoxA(NULL, "dat boi not found", NULL, MB_OK);
					}
				}
			}

			return true;
		}

		bool OnStart(cIGZCOM* pCOM) {
			cIGZFrameWork* const pFramework = RZGetFrameWork();
			if (pFramework) {
				if (pFramework->GetState() < cIGZFrameWork::kStatePreAppInit) {
					pFramework->AddHook(this);
				}
				else {
					PreAppInit();
				}
			}
			return true;
		}
};

// You need to replace the director returned here for the game and this DLL
// to use the right director. This is the only place that it's necessary to
// do so.
cRZCOMDllDirector* RZGetCOMDllDirector() {
	static cSC4ExtraCheatsPluginCOMDirector sDirector;
	return &sDirector;
}