/* JSON VALUE (IMPLEMENTATION)
 * 
 * This object wraps the functionality of the Json::Value class
 *
 * March 30, 2010 David McKeone (Created)
 */

#include "jsoncpp.he"
#include "JsonValue.he"

#include <string>

using boost::shared_ptr;

// Resource #'s for Value Type constants
const static qshort kConstValueTypeStart = 23001,
                    kConstValueTypeEnd   = 23008;


using namespace OmnisTools;

/**************************************************************************************************
 **                       CONSTRUCTORS / DESTRUCTORS                                             **
 **************************************************************************************************/

JsonValue::JsonValue(qobjinst objinst) : NVObjBase(objinst), document(new Json::Value())
{ 
	jsonValue = &(*document);
}

JsonValue::JsonValue(qobjinst objinst, tThreadData *pThreadData) : NVObjBase(objinst), document(new Json::Value())
{ 
	jsonValue = &(*document);
	
	// Constructor for $new(), interpret parameters (if any)
	pThreadData->mCurMethodName = "$new";
	qshort paramCount = ECOgetParamCount(pThreadData->mEci);
		
	methodInitialize(pThreadData, paramCount);
}

JsonValue::~JsonValue()
{ }

void JsonValue::copy( NVObjBase* pObj ) {
	// Copy in super class (This does *this = *pObj)
	NVObjBase::copy(pObj);
	
	// Copy the Json::Value and top pointer into the new object
	jsonValue = dynamic_cast<JsonValue*>(pObj)->jsonValue;
	document = dynamic_cast<JsonValue*>(pObj)->document;
}

// Get the internal Json::Value
Json::Value& JsonValue::getJsonValue() {
	return *jsonValue;
}

// Set the internal Json::Value
void JsonValue::setJsonValue(shared_ptr<Json::Value> v) {
	// Set the new value
	document = v;
	// Set the current data pointer
	jsonValue = &(*document);
}

void JsonValue::setJsonValue(boost::shared_ptr<Json::Value> v, Json::Value* pos) {
	// Set the new value
	document = v;
	// Set the current data pointer
	jsonValue = pos;
}

/**************************************************************************************************
 **                              PROPERTY DECLERATION                                            **
 **************************************************************************************************/

// This is where the resource # of the methods is defined.  In this project it is also used as the Unique ID.
//
// NOTE: Json::Value properties are on the 3100-3199 stripe
const static qshort cPropertyValueType     = 3100,
                    cPropertyValueTypeDesc = 3101,
                    cPropertyContents      = 3102;

/**************************************************************************************************
 **                               METHOD DECLERATION                                             **
 **************************************************************************************************/

// This is where the resource # of the methods is defined.  In this project is also used as the Unique ID.
//
// NOTE:Json::Value has the 2100-2199 stripe
const static qshort cMethodConstruct  = 2100,
                    cMethodInitialize = 2101,
                    cMethodIsNull     = 2102,
                    cMethodIsBool     = 2103,
                    cMethodIsInt      = 2104,
                    cMethodIsUInt     = 2105,
                    cMethodIsIntegral = 2106,
                    cMethodIsDouble   = 2107,
                    cMethodIsNumeric  = 2108,
                    cMethodIsString   = 2109,
                    cMethodIsArray    = 2110,
                    cMethodIsObject   = 2111,
                    cMethodGet        = 2112,
                    cMethodSize       = 2113,
                    cMethodEmpty      = 2114,
                    cMethodClear      = 2115,
                    cMethodIsValidIndex = 2116,
                    cMethodIsMember = 2117,
                    cMethodGetMemberNames = 2118,
					cMethodCopy = 2119,
					cMethodRoot = 2120,
					cMethodSet  = 2121;

/**************************************************************************************************
 **                                 INSTANCE METHODS                                             **
 **************************************************************************************************/

// Call a method
qlong JsonValue::methodCall( tThreadData* pThreadData )
{
	qshort funcId = (qshort)ECOgetId(pThreadData->mEci);
	qshort paramCount = ECOgetParamCount(pThreadData->mEci);

	switch( funcId )
	{
		case cMethodConstruct:
			pThreadData->mCurMethodName = "$construct";
			methodConstruct(pThreadData, paramCount);
			break;
		case cMethodInitialize:
			pThreadData->mCurMethodName = "$initialize";
			methodInitialize(pThreadData, paramCount);
			break;
		case cMethodIsNull:
			pThreadData->mCurMethodName = "$isNull";
			methodIsNull(pThreadData, paramCount);
			break;
		case cMethodIsBool:
			pThreadData->mCurMethodName = "$isBool";
			methodIsBool(pThreadData, paramCount);
			break;
		case cMethodIsInt:
			pThreadData->mCurMethodName = "$isInt";
			methodIsInt(pThreadData, paramCount);
			break;
		case cMethodIsUInt:
			pThreadData->mCurMethodName = "$isUInt";
			methodIsUInt(pThreadData, paramCount);
			break;
		case cMethodIsIntegral:
			pThreadData->mCurMethodName = "$isIntegral";
			methodIsIntegral(pThreadData, paramCount);
			break;
		case cMethodIsDouble:
			pThreadData->mCurMethodName = "$isDouble";
			methodIsDouble(pThreadData, paramCount);
			break;
		case cMethodIsNumeric:
			pThreadData->mCurMethodName = "$isNumeric";
			methodIsNumeric(pThreadData, paramCount);
			break;
		case cMethodIsString:
			pThreadData->mCurMethodName = "$isString";
			methodIsString(pThreadData, paramCount);
			break;
		case cMethodIsArray:
			pThreadData->mCurMethodName = "$isArray";
			methodIsArray(pThreadData, paramCount);
			break;
		case cMethodIsObject:
			pThreadData->mCurMethodName = "$isObject";
			methodIsObject(pThreadData, paramCount);
			break;
		case cMethodGet:
			pThreadData->mCurMethodName = "$get";
			methodGet(pThreadData, paramCount);
			break;
		case cMethodSize:
			pThreadData->mCurMethodName = "$size";
			methodSize(pThreadData, paramCount);
			break;
		case cMethodEmpty:
			pThreadData->mCurMethodName = "$empty";
			methodEmpty(pThreadData, paramCount);
			break;
		case cMethodClear:
			pThreadData->mCurMethodName = "$clear";
			methodClear(pThreadData, paramCount);
			break;
		case cMethodIsValidIndex:
			pThreadData->mCurMethodName = "$isValidIndex";
			methodIsValidIndex(pThreadData, paramCount);
			break;
		case cMethodIsMember:
			pThreadData->mCurMethodName = "$isMember";
			methodIsMember(pThreadData, paramCount);
			break;
		case cMethodGetMemberNames:
			pThreadData->mCurMethodName = "$getMemberNames";
			methodGetMemberNames(pThreadData, paramCount);
			break;
		case cMethodCopy:
			pThreadData->mCurMethodName = "$copy";
			methodCopy(pThreadData, paramCount);
			break;
		case cMethodRoot:
			pThreadData->mCurMethodName = "$root";
			methodRoot(pThreadData, paramCount);
			break;
		case cMethodSet:
			pThreadData->mCurMethodName = "$set";
			methodSet(pThreadData, paramCount);
			break;
	}

	return 0L;
}

/**************************************************************************************************
 **                                        STATIC METHODS                                        **
 **************************************************************************************************/

/* METHODS */

// Table of parameter resources and types.
// Note that all parameters can be stored in this single table and the array offset can be  
// passed via the MethodsTable.
//
// Columns are:
// 1) Name of Parameter (Resource #)
// 2) Return type (fft value)
// 3) Parameter flags of type EXTD_FLAG_xxxx
// 4) Extended flags.  Documentation states, "Must be 0"
//
// NOTE: Json::Value has the 4000-4099 parameter stripe
ECOparam cJsonValueMethodsParamsTable[] = 
{
	4000, fftCharacter, 0, 0,
	4001, fftCharacter, 0, 0,
	4002, fftCharacter, 0, 0,
	4003, fftObject, EXTD_FLAG_PARAMOPT, 0,
	4004, fftInteger, 0, 0,
	4005, fftCharacter, 0, 0
};

// Table of Methods available for Simple
// Columns are:
// 1) Unique ID 
// 2) Name of Method (Resource #)
// 3) Return Type 
// 4) # of Parameters
// 5) Array of Parameter Names (Taken from MethodsParamsTable.  Increments # of parameters past this pointer) 
// 6) Enum Start (Not sure what this does, 0 = disabled)
// 7) Enum Stop (Not sure what this does, 0 = disabled)
ECOmethodEvent cJsonValueMethodsTable[] = 
{
	cMethodConstruct, cMethodConstruct, fftCharacter, 1, &cJsonValueMethodsParamsTable[0], 0, 0,
	cMethodInitialize, cMethodInitialize, fftCharacter, 1, &cJsonValueMethodsParamsTable[1], 0, 0,
	cMethodIsNull, cMethodIsNull, fftNone, 0, 0, 0, 0,
	cMethodIsBool, cMethodIsBool, fftNone, 0, 0, 0, 0,
	cMethodIsInt, cMethodIsInt, fftNone, 0, 0, 0, 0,
	cMethodIsUInt, cMethodIsUInt, fftNone, 0, 0, 0, 0,
	cMethodIsIntegral, cMethodIsIntegral, fftNone, 0, 0, 0, 0,
	cMethodIsDouble, cMethodIsDouble, fftNone, 0, 0, 0, 0,
	cMethodIsNumeric, cMethodIsNumeric, fftNone, 0, 0, 0, 0,
	cMethodIsString, cMethodIsString, fftNone, 0, 0, 0, 0,
	cMethodIsArray, cMethodIsArray, fftNone, 0, 0, 0, 0,
	cMethodIsObject, cMethodIsObject, fftNone, 0, 0, 0, 0,
	cMethodGet, cMethodGet, fftObject, 2, &cJsonValueMethodsParamsTable[2], 0, 0,
	cMethodSize, cMethodSize, fftInteger, 0, 0, 0, 0,
	cMethodEmpty, cMethodEmpty, fftBoolean, 0, 0, 0, 0,
	cMethodClear, cMethodClear, fftNone, 0, 0, 0, 0,
	cMethodIsValidIndex, cMethodIsValidIndex, fftBoolean, 1, &cJsonValueMethodsParamsTable[4], 0, 0,
	cMethodIsMember, cMethodIsMember, fftBoolean, 1, &cJsonValueMethodsParamsTable[5], 0, 0,
	cMethodGetMemberNames, cMethodGetMemberNames, fftList, 0, 0, 0, 0,
	cMethodCopy, cMethodCopy, fftObject, 0, 0, 0, 0,
	cMethodRoot, cMethodRoot, fftObject, 0, 0, 0, 0,
	cMethodSet, cMethodSet, fftNone, 0, 0, 0, 0
};

// List of methods in Simple
qlong JsonValue::returnMethods(tThreadData* pThreadData)
{
	const qshort cMethodCount = sizeof(cJsonValueMethodsTable) / sizeof(ECOmethodEvent);
	
	return ECOreturnMethods( gInstLib, pThreadData->mEci, &cJsonValueMethodsTable[0], cMethodCount );
}

/* PROPERTIES */

// Table of properties available from Simple
// Columns are:
// 1) Unique ID 
// 2) Name of Property (Resource #)
// 3) Return Type 
// 4) Flags describing the property
// 5) Additional Flags describing the property
// 6) Enum Start (Not sure what this does, 0 = disabled)
// 7) Enum Stop (Not sure what this does, 0 = disabled)
ECOproperty cJsonValuePropertyTable[] = 
{
	cPropertyValueType    , cPropertyValueType    , fftInteger  , EXTD_FLAG_PROPCUSTOM|EXTD_FLAG_EXTCONSTANT, 0, kConstValueTypeStart, kConstValueTypeEnd, /* Shows under Custom category */
	cPropertyValueTypeDesc, cPropertyValueTypeDesc, fftCharacter, EXTD_FLAG_PROPCUSTOM, 0, 0, 0, /* Shows under Custom category */
	cPropertyContents, cPropertyContents, fftCharacter, EXTD_FLAG_PROPCUSTOM, 0, 0, 0  /* Shows under Custom category */
};

// List of properties in this component
qlong JsonValue::returnProperties( tThreadData* pThreadData )
{
	const qshort propertyCount = sizeof(cJsonValuePropertyTable) / sizeof(ECOproperty);

	return ECOreturnProperties( gInstLib, pThreadData->mEci, &cJsonValuePropertyTable[0], propertyCount );
}

// Assignability of properties
qlong JsonValue::canAssignProperty( tThreadData* pThreadData, qlong propID ) {
	switch (propID) {
		case cPropertyValueType:
			return qfalse;
		case cPropertyValueTypeDesc:
			return qfalse;
		case cPropertyContents:
			return qfalse;
		default:
			return qfalse;
	}
}

// Method to retrieve a property of the object
qlong JsonValue::getProperty( tThreadData* pThreadData ) 
{
	EXTfldval fValReturn;
	
	qlong propID = ECOgetId( pThreadData->mEci );
	switch( propID ) {
		case cPropertyValueType:
			propertyValueType(fValReturn); // Put property into return value
			break;
		case cPropertyValueTypeDesc:
			propertyValueTypeDesc(fValReturn); // Put property into return value
			break;
		case cPropertyContents:
			getPropertyContents(fValReturn, pThreadData); // Put property into return value
			break;		    
	}
	
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
	
	return 1L;
}

// Method to set a property of the object
qlong JsonValue::setProperty( tThreadData* pThreadData )
{	
	// Retrieve value to set for property, always in first parameter
	EXTfldval fVal;
	if( getParamVar( pThreadData->mEci, 1, fVal) == qfalse ) 
		return qfalse;
	
	// Assign to the appropriate property
	qlong propID = ECOgetId( pThreadData->mEci );
	switch( propID ) {
		case cPropertyValueType:
			// Value type is not an assignable property
			return qfalse;
		case cPropertyValueTypeDesc:
			// Value type description is not an assignable property
			return qfalse;
		case cPropertyContents:
			// Value type description is not an assignable property
			return qfalse;
		default:
			return qfalse;
	}
}

/**************************************************************************************************
 **                                         PROPERTIES                                           **
 **************************************************************************************************/

void JsonValue::propertyValueType(EXTfldval &retVal) {
	switch (jsonValue->type()) {
		case Json::nullValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 0);
			break;
		case Json::intValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 1);
			break;
		case Json::uintValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 2);
			break;
		case Json::realValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 3);
			break;
		case Json::stringValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 4);
			break;
		case Json::booleanValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 5);
			break;
		case Json::arrayValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 6);
			break;
		case Json::objectValue:
			retVal.setConstant(kConstValueTypeStart, kConstValueTypeEnd, 7);
			break;
		default:
			break;
	}
}

// Returns the text version of the constant name
void JsonValue::propertyValueTypeDesc(EXTfldval &retVal) {
	switch (jsonValue->type()) {
		case Json::nullValue:
			getEXTFldValFromString(retVal,"kJSONNullValueType");
			break;
		case Json::intValue:
			getEXTFldValFromString(retVal,"kJSONIntValueType");
			break;
		case Json::uintValue:
			getEXTFldValFromString(retVal,"kJSONUIntValueType");
			break;
		case Json::realValue:
			getEXTFldValFromString(retVal,"kJSONRealValueType");
			break;
		case Json::stringValue:
			getEXTFldValFromString(retVal,"kJSONStringValueType");
			break;
		case Json::booleanValue:
			getEXTFldValFromString(retVal,"kJSONBooleanValueType");
			break;
		case Json::arrayValue:
			getEXTFldValFromString(retVal,"kJSONArrayValueType");
			break;
		case Json::objectValue:
			getEXTFldValFromString(retVal,"kJSONObjectValueType");
			break;
		default:
			break;
	}
}

// Return the contents of this value to the caller
void JsonValue::getPropertyContents(EXTfldval &retVal, tThreadData* pThreadData) {
	switch (jsonValue->type()) {
		case Json::nullValue:
			retVal.setNull(fftCharacter, dpFcharacter);
			break;
		case Json::intValue:
			retVal.setLong(jsonValue->asInt());
			break;
		case Json::uintValue:
			retVal.setLong(jsonValue->asUInt());
			break;
		case Json::realValue:
			retVal.setNum(jsonValue->asDouble());
			break;
		case Json::stringValue:
			getEXTFldValFromString(retVal,jsonValue->asString());
			break;
		case Json::booleanValue:
			retVal.setBool( getQBoolFromBool(jsonValue->asBool()) );
			break;
		case Json::arrayValue:
			getEXTFldValFromString(retVal,"<JSON Array>");
			break;
		case Json::objectValue:
			getEXTFldValFromString(retVal,"<JSON Object>");
			break;
		default:
			break;
	}
}

void JsonValue::getEXTfldvalForValue(tThreadData* pThreadData, EXTfldval &retVal, UInt indexValue) {
	Json::Value* posPointer = &((*jsonValue)[indexValue]);
	getEXTfldvalForValue(pThreadData, retVal, posPointer);
}

void JsonValue::getEXTfldvalForValue(tThreadData* pThreadData, EXTfldval &retVal, std::string keyValue) {
	Json::Value* posPointer = &((*jsonValue)[keyValue]);
	getEXTfldvalForValue(pThreadData, retVal, posPointer);
}

void JsonValue::getEXTfldvalForValue(tThreadData* pThreadData, EXTfldval &retVal, Json::Value* posPointer) {
	// Create return value object
	JsonValue *newObj = createNVObj<JsonValue>(pThreadData);
	if ( posPointer != 0 ) {
		// Return pointer to found position
		newObj->setJsonValue(document, posPointer); // Set value and pointer to source
	} else {
		// Create and return new null object
		shared_ptr<Json::Value> nullObj(new Json::Value());
		newObj->setJsonValue(nullObj);
	}
	
	retVal.setObjInst( newObj->mObjInst, qtrue );
}

// Helper method to initialize the jsonValue to a new value.
void JsonValue::setValueFromEXTfldval(tThreadData* pThreadData, EXTfldval &fVal) {
	// Get the data type of the parameter
	ffttype valType; fVal.getType(valType);
	
	// Perform appropriate initialization for each type
	if (valType == fftCharacter) {
		*jsonValue = getStringFromEXTFldVal(fVal);
	} else if (valType == fftInteger) {
		*jsonValue = static_cast<int>( fVal.getLong() );
	} else if (valType == fftNumber) {
		*jsonValue = getDoubleFromEXTFldVal(fVal);
	} else if (valType == fftBoolean) {
		*jsonValue = getBoolFromQBool(fVal.getBool());
	} else if (valType == fftObject) {
		JsonValue* assignObj = getObjForEXTfldval<JsonValue>(pThreadData, fVal);
		if (assignObj) {
			*jsonValue = *(assignObj->jsonValue);
		}
	}
}

// Helper method to set the jsonValue for a specific array position
void JsonValue::setValueFromEXTfldval(tThreadData* pThreadData, EXTfldval &fVal, int group) {
	// Get the data type of the parameter
	ffttype valType; fVal.getType(valType);
	
	// Perform appropriate initialization for each type
	if (valType == fftCharacter) {
		(*jsonValue)[group] = getStringFromEXTFldVal(fVal);
	} else if (valType == fftInteger) {
		(*jsonValue)[group] = static_cast<int>( fVal.getLong() );
	} else if (valType == fftNumber) {
		(*jsonValue)[group] = getDoubleFromEXTFldVal(fVal);
	} else if (valType == fftBoolean) {
		(*jsonValue)[group] = getBoolFromQBool(fVal.getBool());
	}
}

// Helper method to set the jsonValue for a specific group
void JsonValue::setValueFromEXTfldval(tThreadData* pThreadData, EXTfldval &fVal, std::string group) {
	(*jsonValue)[group] = Json::Value();
	
	// Get the data type of the parameter
	ffttype valType; fVal.getType(valType);
	
	// Perform appropriate initialization for each type
	if (valType == fftCharacter) {
		(*jsonValue)[group] = getStringFromEXTFldVal(fVal);
	} else if (valType == fftInteger) {
		(*jsonValue)[group] = static_cast<int>( fVal.getLong() );
	} else if (valType == fftNumber) {
		(*jsonValue)[group] = getDoubleFromEXTFldVal(fVal);
	} else if (valType == fftBoolean) {
		(*jsonValue)[group] = getBoolFromQBool(fVal.getBool());
	}
	
	// If no parameters were passed or an object couldn't be found, then init to NULL
	if ( (*jsonValue)[group].isNull() ) {
		(*jsonValue)[group] = Json::Value();
	}
}

// Helper method to initialize the jsonValue to a new value.
void JsonValue::setValueFromParameter(tThreadData *pThreadData, qshort paramNumber) {
	EXTParamInfo* param = ECOfindParamNum( pThreadData->mEci, paramNumber );
	if( param ) { 
		// Interpret the parameter we have
		EXTfldval fVal; fVal.setFldVal((qfldval)param->mData);
		
		setValueFromEXTfldval(pThreadData, fVal);
	}
}

/**************************************************************************************************
 **                                            METHODS                                           **
 **************************************************************************************************/

// Construct method
void JsonValue::methodConstruct( tThreadData* pThreadData, qshort pParamCount ) {
	// Pass through to initialize
	methodInitialize(pThreadData, pParamCount);
}

// Initialize method
void JsonValue::methodInitialize( tThreadData* pThreadData, qshort pParamCount )
{
	// Set the current method name
	if (pThreadData->mCurMethodName != "$new") {
		pThreadData->mCurMethodName = "$initialize";
	}
	
	setValueFromParameter(pThreadData, 1);
}

// Status methods
void JsonValue::methodIsNull( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isNull());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsBool( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isBool());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsInt( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isInt());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsUInt( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isUInt());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsIntegral( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isIntegral());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsDouble( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isDouble());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsNumeric( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isNumeric());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsString( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isString());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsArray( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isArray());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

void JsonValue::methodIsObject( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval fValReturn;
	qbool result = getQBoolFromBool(jsonValue->isObject());
	
	fValReturn.setBool(result); // Put property into return value
	ECOaddParam(pThreadData->mEci, &fValReturn); // Return to caller
}

// JsonValue retrieval.  This implements the operator[] and $get() methods for Json::Value since there are no operators in Omnis.
// Call with $get('Settings') for settings key in object or $get(0) for an array
void JsonValue::methodGet( tThreadData* pThreadData, qshort pParamCount )
{
	EXTfldval keyVal, defVal, retVal;
	
	if ( getParamVar(pThreadData, 1, keyVal) == qfalse)
		return;
	
	std::string keyValue;
	UInt indexValue;
	ffttype valType; keyVal.getType(valType);
	
	if (valType == fftInteger) {
		if (jsonValue->isArray()) {
			indexValue = static_cast<UInt>( keyVal.getLong() );
			getEXTfldvalForValue(pThreadData, retVal, indexValue);
		}
	} else if (valType == fftCharacter) {
		if (jsonValue->isObject()) {
			keyValue = getStringFromEXTFldVal( keyVal );
			getEXTfldvalForValue(pThreadData, retVal, keyValue);
			
		}
	}
	
	ECOaddParam( pThreadData->mEci, &retVal );
}

// Create a copy of the pointer at the current position.  This copied pointer is trimmed above the current position.
void JsonValue::methodCopy( tThreadData* pThreadData, qshort pParamCount ) {
	shared_ptr<Json::Value> copyValue(new Json::Value(*jsonValue));
	
	JsonValue *newObj = createNVObj<JsonValue>(pThreadData);
	newObj->setJsonValue(copyValue);
	
	EXTfldval retVal;
	retVal.setObjInst( newObj->mObjInst, qtrue ); 
	ECOaddParam( pThreadData->mEci, &retVal );
}

// Get a pointer to the root of the current object
void JsonValue::methodRoot( tThreadData* pThreadData, qshort pParamCount ) {
	JsonValue *newObj = createNVObj<JsonValue>(pThreadData);
	newObj->setJsonValue(document);
	
	EXTfldval retVal;
	retVal.setObjInst( newObj->mObjInst, qtrue ); 
	ECOaddParam( pThreadData->mEci, &retVal );
}

// Return size
void JsonValue::methodSize( tThreadData* pThreadData, qshort pParamCount ) {
	// Get size from value object
	int size = jsonValue->size();
	qlong qsize = static_cast<qlong>(size);
	
	// Return to Omnis
	EXTfldval fValReturn;
	fValReturn.setLong(qsize); 
	ECOaddParam(pThreadData->mEci, &fValReturn);
}

// Returns true if Value object empty
void JsonValue::methodEmpty( tThreadData* pThreadData, qshort pParamCount ) {
	// Get size from value object
	qbool status = getQBoolFromBool( jsonValue->empty() );
	
	// Return to Omnis
	EXTfldval fValReturn;
	fValReturn.setBool(status); 
	ECOaddParam(pThreadData->mEci, &fValReturn);
}

// Clears the contents of the Value object
void JsonValue::methodClear( tThreadData* pThreadData, qshort pParamCount ) {
	jsonValue->clear();
}

// Returns true if the index is in the array
void JsonValue::methodIsValidIndex( tThreadData* pThreadData, qshort pParamCount ) {
	EXTfldval indexVal, retVal;
	
	if ( getParamVar(pThreadData, 1, indexVal) == qfalse)
		return;
	
	int index = indexVal.getLong();
	
	// Send key to Value object
	qbool status = getQBoolFromBool( jsonValue->isValidIndex(index) );
	
	// Return to Omnis
	EXTfldval fValReturn;
	fValReturn.setBool(status); 
	ECOaddParam(pThreadData->mEci, &fValReturn);
}

// Return true if key (param 1) is in the object
void JsonValue::methodIsMember( tThreadData* pThreadData, qshort pParamCount ) {
	
	EXTfldval keyVal, retVal;
	
	if ( getParamVar(pThreadData, 1, keyVal) == qfalse)
		return;
	
	std::string key = getStringFromEXTFldVal(keyVal);
	
	// Send key to Value object
	qbool status = getQBoolFromBool( jsonValue->isMember(key) );
	
	// Return to Omnis
	EXTfldval fValReturn;
	fValReturn.setBool(status); 
	ECOaddParam(pThreadData->mEci, &fValReturn);
}

// Return list of values in object
void JsonValue::methodGetMemberNames( tThreadData* pThreadData, qshort pParamCount ) {
	// Create return value
	EXTfldval fValReturn, fValMember, fValColName;
	
	// Create single column list
	EXTqlist *retList = new EXTqlist( listVlen );  
	
	getEXTFldValFromString(fValColName, "Member");
	str255 colName; fValColName.getChar(colName, qtrue);
	retList->addCol(fftCharacter, dpFcharacter, 10000000, &colName);
	
	// Ensure that the Json::Value is an Object (since those are the only one's with member names)
	if ( !(jsonValue->isObject()) ) {
		fValReturn.setList(retList, qtrue, qfalse); 
		ECOaddParam(pThreadData->mEci, &fValReturn);
		return;
	}
	
	Json::Value::Members memberNames = jsonValue->getMemberNames();
	
	// Loop the member names to create the list
	std::string rowMember;
	for (qlong lineNumber = 0; lineNumber < static_cast<qlong>(memberNames.size()); lineNumber++) {
		
		retList->insertRow(0);
		//retList->setCurRow( lineNumber+1 );
		retList->getColValRef(lineNumber+1, 1, fValMember, qtrue);
		
		// Retrieve member name and place it in the list
		rowMember = memberNames[lineNumber];
		getEXTFldValFromString(fValMember, rowMember);
	}
	
	fValReturn.setList(retList, qtrue, qfalse); 
	ECOaddParam(pThreadData->mEci, &fValReturn);
	return;
}

// This method sets the value for the current position to the first parameter
void JsonValue::methodSet( tThreadData* pThreadData, qshort pParamCount) {
	EXTfldval fVal;
	
	if ( getParamVar(pThreadData, 1, fVal) == qfalse)
		return;
	
	setValueFromEXTfldval(pThreadData, fVal);
}

