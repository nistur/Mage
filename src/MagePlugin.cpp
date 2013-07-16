#include "MagePlugin.h"

//------------------------------------------------------------------------------
// Plugins
//------------------------------------------------------------------------------
#include "MEmbedFilePlugin.h"
#include "MScriptPlugin.h"
#include "MEventPlugin.h"
#include "MSaveFilePlugin.h"
#include "MScriptableBehaviourPlugin.h"

//------------------------------------------------------------------------------
#include "MEmbedFile.h"

//------------------------------------------------------------------------------
// Embedded files
// These are just the data from the files, so we don't need headers
//------------------------------------------------------------------------------
#include "mageLua.c"
#include "mage_inventoryLua.c"

#include "PointOfInterestLua.c"

//------------------------------------------------------------------------------
// Wrapper macros
//------------------------------------------------------------------------------
#define EMBED(dir, file)\
	MEmbedFileGetNew(dir##file##_lua, dir##file##Name, dir##file, dir##file##Size);
#define UNEMBED(dir, file)\
	if(dir##file##_lua) { dir##file##_lua->destroy(); dir##file##_lua = NULL; }
#define EMBEDDED(dir, file)\
	MEmbedFile* dir##file##_lua = NULL;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Embedded files
//------------------------------------------------------------------------------
EMBEDDED(scripts, mage);
EMBEDDED(scripts, mage_inventory);

EMBEDDED(behaviors, PointOfInterest);

//------------------------------------------------------------------------------
void StartPlugin(void)
{
	//--------------------------------------------------------------------------
	// Start all the plugins (1.2.3...)
	//--------------------------------------------------------------------------
	MPluginStart(MEmbedFile);
	MPluginStart(MScriptExt);
    MPluginStart(MEvent);
    MPluginStart(MSaveFile);

	//--------------------------------------------------------------------------
	// Add embedded files
	//--------------------------------------------------------------------------
    EMBED(scripts, mage);
    EMBED(scripts, mage_inventory);

	// behaviours don't currently work because readDirectory doesn't allow for
	// our virtual filesystem yet
    EMBED(behaviors, PointOfInterest);

    // MScriptableBehaviour should start after we've added all embedded files
    MPluginStart(MScriptableBehaviour);
}

//------------------------------------------------------------------------------
void EndPlugin(void)
{
	//--------------------------------------------------------------------------
	// Remove embedded files
	//--------------------------------------------------------------------------
	UNEMBED(behaviors, PointOfInterest);

	UNEMBED(scripts, mage_inventory);
	UNEMBED(scripts, mage);

	//--------------------------------------------------------------------------
	// End all the plugins (...3.2.1)
	//--------------------------------------------------------------------------
	MPluginEnd(MScriptableBehaviour);
    MPluginEnd(MSaveFile);
    MPluginEnd(MEvent);
    MPluginEnd(MScriptExt);
	MPluginEnd(MEmbedFile);
}