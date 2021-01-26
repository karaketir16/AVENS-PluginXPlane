/*
Mariana Rodrigues

Based on example made by Luiz Carlos Querino Filho
*/

// Standard includes
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>

// XPlane SDK includes
#include "XPLMPlanes.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMUtilities.h"
#include "XPLMPlugin.h"

// XML includes
#include "tinyXML\tinyxml.h"

// Plugin includes
#include "UserAircraft.h"
#include "MultiAircraft.h"
#include "ConcreteMultiAircraft.h"

#if IBM
#include <windows.h>
BOOL APIENTRY DllMain( HANDLE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

// Definitions and global variables
#define MAX_NUMBER_OF_PLANES 20
#define XML_FILENAME "C:\\tmp\\pluginInterface.xml"

// User Aircraft
UserAircraft * pxAircraft0 = UserAircraft::getUserAircraft();
// Other Aircraft
Aircraft * pxMultiAircraft[MAX_NUMBER_OF_PLANES - 1];

// XML file
TiXmlDocument xConfigDocument(XML_FILENAME);
// Number of planes in simulation
int iNumberOfPlanes = 0;

// Control flag
bool bFirstLoop = TRUE;


// Function directives

// fWaitForFileCallback --- stands by until file is created by OMNET++
static float fWaitForFileCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon);

// fFlightCallback --- update Plane position everytime
static float fFlightCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon);

void vDeallocateVector(void){
	for (int iAux = 1; (iAux < MAX_NUMBER_OF_PLANES - 1); iAux++) {
		if(pxMultiAircraft[iAux] != NULL){
			delete pxMultiAircraft[iAux];
			pxMultiAircraft[iAux] = NULL;
		}
	}
}



PLUGIN_API int XPluginStart(char * outName, char * outSig,char * outDesc)
{
	strcpy(outName, "PluginOMNeTpp");
	strcpy(outSig, "avens");
	strcpy(outDesc, "A plugin that integrates X-Plane and OMNeT++.");

	// Disable AI for each aircraft.
	for (int AircraftIndex = 1; AircraftIndex < 19; AircraftIndex++)
		XPLMDisableAIForPlane(AircraftIndex);



	XPLMDebugString("Leave Plugin Start");
	return 1;
}

PLUGIN_API void	XPluginStop(void)
{
	//Unregister Callbacks
	XPLMDebugString("Enter Plugin Stop");

	XPLMUnregisterFlightLoopCallback(fWaitForFileCallback, NULL);
	XPLMUnregisterFlightLoopCallback(fFlightCallback, NULL);

	// Delete ConcreteMultiAircraft vector
	for (int iAux = 1; (iAux < iNumberOfPlanes - 1); iAux++) {
		delete pxMultiAircraft[iAux];
		pxMultiAircraft[iAux] = NULL;
	}
	XPLMDebugString("Leave plugin stop \n");

}

PLUGIN_API void XPluginDisable(void)
{

	XPLMDebugString("XPluginDisabled\n");
}

PLUGIN_API int XPluginEnable(void)
{
	bFirstLoop = TRUE;
	XPLMRegisterFlightLoopCallback(
		fWaitForFileCallback,	/* Callback */
		1.0,					/* Interval */
		NULL);					/* refcon not used. */
	XPLMDebugString("XPluginEnable\n");
	return 1;
}

PLUGIN_API void XPluginReceiveMessage(	XPLMPluginID	inFromWho,
									  int				inMessage,
									  void *			inParam)
{
	char messageNumber[10];
	XPLMDebugString("XPluginReceiveMessage Number ");
	int n = sprintf(messageNumber,"%d\n\0",inMessage);
	XPLMDebugString(messageNumber);
}

//-----------------------------------------------------------------------------
// fWaitForFileCallback - Stands by until file is created by OMNET++
float fWaitForFileCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon){

	// Verify if file has been created
	if (xConfigDocument.LoadFile() == true) {

		// Configuration file exists
		XPLMDebugString("File Exists\n");

		// Read parameter - Number of Planes
		TiXmlElement * xNumberOfPlanesElement = xConfigDocument.FirstChildElement("Number_of_Planes");
		XPLMDebugString("Read Number of Planes\n");
		if(xNumberOfPlanesElement == NULL){
			// Lack of required parameter --- exit callback and never call it again.
			XPLMDebugString("No Parameter 'Number_of_Planes'. No further actions will be taken.");
			return 0;
		}
		xNumberOfPlanesElement->QueryIntAttribute("value",&iNumberOfPlanes);
		//delete xNumberOfPlanesElement;

		XPLMDebugString("Reading Planes\n");
		// Read Planes
		if(iNumberOfPlanes > 0){
			// Read FANET
			XPLMDebugString("Before reading FANET\n");
			TiXmlElement * xFANET = xConfigDocument.FirstChildElement("FANET");
			//TiXmlElement * xFANET = xNumberOfPlanesElement->NextSiblingElement("FANET");

			if(xFANET == NULL){
				// Lack of required parameter --- exit callback and never call it again.
				XPLMDebugString("No Parameter 'FANET'. No further actions will be taken.");
				return 0;
			}

			XPLMDebugString("Reading Planes\n");
			TiXmlNode * xPlane = NULL;
			for(int iIndex = 0; iIndex < iNumberOfPlanes; iIndex++){
				int iPlaneID;
				TiXmlNode * xPreviousPlane = xPlane;
				xPlane = xFANET->IterateChildren("Aircraft",xPreviousPlane);

				if(xPlane == NULL){
					// Missing planes
					XPLMDebugString("Missing planes in XML file. No further actions will be taken.\n");
					vDeallocateVector();
					return 0;
				}
				xPlane->ToElement()->QueryIntAttribute("id",&iPlaneID);
				if (iPlaneID > 0) {
					// Not User Plane
					if (iPlaneID != iIndex) {
						// Planes out of order
						XPLMDebugString("Planes out of order. No further actions will be taken.\n");
						vDeallocateVector();
						return 0;
					} else {
						pxMultiAircraft[iIndex] = new ConcreteMultiAircraft(iPlaneID,(ConcreteMultiAircraft::ePlanePosition) (iPlaneID - 1));
						//pxMultiAircraft[iIndex] = new ConcreteMultiStraight(iPlaneID);
						char msg[80];
						sprintf(msg,"Created ConcreteMultiAircraft index %d",iIndex);
						XPLMDebugString(msg);
					}
				}
			}
			//XPLMDebugString("Before deleting xPlane\n");
			//delete xPlane;
			//XPLMDebugString("XPlane deleted\n");
		}else{
			// Number of Planes == 0 colocar aki
			XPLMDebugString("Number of Planes = 0\n");
			return 0;
		}
	}else{
		//XPLMDebugString("File not found");
		return -1;
	}
	//XPLMDebugString("File Loaded OK");

	//unregister file callback, file created by omnet.
	XPLMUnregisterFlightLoopCallback(fWaitForFileCallback, NULL);
	XPLMRegisterFlightLoopCallback(fFlightCallback,2.0,NULL);
	xConfigDocument.SaveFile();

	//delete xFlagElement;

	return 0;
}
//-----------------------------------------------------------------------------
// fFlightCallback --- update Plane position everytime
static float fFlightCallback(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void * inRefcon){


	TiXmlElement * xPlaneAttribute;

	// Get UserAircraft
	UserAircraft * pxAircraft0 = UserAircraft::getUserAircraft();

	// Read DataRefs
	pxAircraft0->vUpdatePosition();

	// Get Altitude
	float fAltitude = pxAircraft0->fGetAltitude();

	MultiAircraft::eGearState eState = MultiAircraft::GEAR_DOWN;
	if (fAltitude > 200){
		eState = MultiAircraft::GEAR_UP;
	}

	// Update positions of Other Aircraft
	for(int iIndex = 1; iIndex < iNumberOfPlanes;iIndex++){
		pxMultiAircraft[iIndex]->vUpdatePosition();
//		pxMultiAircraft[iIndex]->vSetGearDeploy(eState);
	}

	// Update values in file
	if(xConfigDocument.LoadFile() == true){
		//XPLMDebugString("Before reading FANET\n");
		TiXmlElement * xFANET = xConfigDocument.FirstChildElement("FANET");

		if(xFANET == NULL){
			// Lack of required parameter --- exit callback and never call it again.
			XPLMDebugString("No Parameter 'FANET'. No further actions will be taken.");
			return 0;
		}

		//XPLMDebugString("Reading Planes\n");
		TiXmlNode * xPlane = NULL;
		for(int iIndex = 0; iIndex < iNumberOfPlanes; iIndex++){
			int iPlaneID;
			TiXmlNode * xPreviousPlane = xPlane;
			xPlane = xFANET->IterateChildren("Aircraft",xPreviousPlane);

			if(xPlane == NULL){
				// Missing planes
				XPLMDebugString("Missing planes in XML file. No further actions will be taken.\n");
				vDeallocateVector();
				return 0;
			}

			Aircraft * pxAircraft;
			if(iIndex == 0){
				pxAircraft = (Aircraft *) pxAircraft0;
			}else{
				pxAircraft = (Aircraft *) pxMultiAircraft[iIndex];
			}
			TiXmlElement * xPlaneElement = xPlane->ToElement();
			xPlaneElement->SetDoubleAttribute("Latitude",pxAircraft->dGetLatitude());
			xPlaneElement->SetDoubleAttribute("Longitude",pxAircraft->dGetLongitude());
			xPlaneElement->SetDoubleAttribute("Elevation",pxAircraft->dGetElevation());
			xPlaneElement->SetDoubleAttribute("XPosition",pxAircraft->dGetXPosition());
			xPlaneElement->SetDoubleAttribute("YPosition",pxAircraft->dGetYPosition());
			xPlaneElement->SetDoubleAttribute("ZPosition",pxAircraft->dGetZPosition());

			if(bFirstLoop == TRUE){
				TiXmlElement * xFlagElement, * CoordRefsElement;

				// Read parameter flag - Read by XPlane
				xFlagElement = xConfigDocument.FirstChildElement("Read_by_Xplane");
				if(xFlagElement == NULL){
					// Lack of required parameter --- exit callback and never call it again.
					XPLMDebugString("No Parameter 'Read_by_Xplane'. No further actions will be taken.");
					vDeallocateVector();
					return 0;
				}else{
					XPLMDebugString("xFlag not NULL\n");
				}

				// Read parameter Coord_References
				CoordRefsElement = xConfigDocument.FirstChildElement("Coord_References");
				if(CoordRefsElement == NULL){
					// Lack of required parameter --- exit callback and never call it again.
					XPLMDebugString("No Parameter 'Coord_References'. No further actions will be taken.");
					vDeallocateVector();
					return 0;
				}else{
					// Update values
					CoordRefsElement->SetDoubleAttribute("Latitude",(double) pxAircraft0->fGetLatitudeReference());
					CoordRefsElement->SetDoubleAttribute("Longitude",(double) pxAircraft0->fGetLongitudeReference());
					CoordRefsElement->SetDoubleAttribute("Elevation",(double) pxAircraft0->dGetElevation());
				}

				xFlagElement->SetAttribute("value","TRUE");
				bFirstLoop = FALSE;
			}
			xConfigDocument.SaveFile();
		}
	}else{
		//Error reading file
		XPLMDebugString("Can't load file. No further will be taken.");
		return -1;
	}

	return -1;
}
//-----------------------------------------------------------------------------