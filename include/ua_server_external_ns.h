/* This Source Code Form is subject to the terms of the Mozilla Public
*  License, v. 2.0. If a copy of the MPL was not distributed with this 
*  file, You can obtain one at http://mozilla.org/MPL/2.0/.*/

#ifndef UA_SERVER_EXTERNAL_NS_H_
#define UA_SERVER_EXTERNAL_NS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An external application that manages its own data and data model. To plug in
 * outside data sources, one can use
 *
 * - VariableNodes with a data source (functions that are called for read and write access)
 * - An external nodestore that is mapped to specific namespaces
 *
 * If no external nodestore is defined for a nodeid, it is always looked up in
 * the "local" nodestore of open62541. Namespace Zero is always in the local
 * nodestore.
 */

typedef UA_Int32 (*UA_ExternalNodeStore_addNodes)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_AddNodesItem *nodesToAdd, UA_UInt32 *indices,
 UA_UInt32 indicesSize, UA_AddNodesResult* addNodesResults, UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_addReferences)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_AddReferencesItem* referencesToAdd,
 UA_UInt32 *indices,UA_UInt32 indicesSize, UA_StatusCode *addReferencesResults,
 UA_DiagnosticInfo *diagnosticInfos);
 
typedef UA_StatusCode (*UA_ExternalNodeStore_addOneWayReference)
(void *ensHandle, const UA_AddReferencesItem *item);

typedef UA_StatusCode (*UA_ExternalNodeStore_getOneWayReferences)
(void *ensHandle, UA_NodeId *nodeId, UA_UInt32 *referencesSize, UA_ReferenceNode **references);

typedef UA_StatusCode (*UA_ExternalNodeStore_deleteNodes)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_DeleteNodesItem *nodesToDelete, UA_UInt32 *indices,
 UA_UInt32 indicesSize, UA_StatusCode *deleteNodesResults, UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_deleteReferences)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_DeleteReferencesItem *referenceToDelete,
 UA_UInt32 *indices, UA_UInt32 indicesSize, UA_StatusCode deleteReferencesresults,
 UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_readNodes)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_ReadValueId *readValueIds, UA_UInt32 *indices,
 UA_UInt32 indicesSize,UA_DataValue *readNodesResults, UA_Boolean timeStampToReturn,
 UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_writeNodes)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_WriteValue *writeValues, UA_UInt32 *indices,
 UA_UInt32 indicesSize, UA_StatusCode *writeNodesResults, UA_DiagnosticInfo *diagnosticInfo);

typedef UA_Int32 (*UA_ExternalNodeStore_browseNodes)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_BrowseDescription *browseDescriptions,
 UA_UInt32 *indices, UA_UInt32 indicesSize, UA_UInt32 requestedMaxReferencesPerNode,
 UA_BrowseResult *browseResults, UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_translateBrowsePathsToNodeIds)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_BrowsePath *browsePath, UA_UInt32 *indices,
 UA_UInt32 indicesSize, UA_BrowsePathResult *browsePathResults, UA_DiagnosticInfo *diagnosticInfos);

typedef UA_Int32 (*UA_ExternalNodeStore_call)
(void *ensHandle, const UA_RequestHeader *requestHeader, UA_CallMethodRequest *request, UA_UInt32 *indices,
 UA_UInt32 indicesSize,UA_CallMethodResult *results);
 
typedef UA_Int32 (*UA_ExternalNodeStore_delete)(void *ensHandle);

typedef struct UA_ExternalNodeStore {
    void *ensHandle;
    UA_ExternalNodeStore_addNodes addNodes;
    UA_ExternalNodeStore_deleteNodes deleteNodes;
    UA_ExternalNodeStore_writeNodes writeNodes;
    UA_ExternalNodeStore_readNodes readNodes;
    UA_ExternalNodeStore_browseNodes browseNodes;
    UA_ExternalNodeStore_translateBrowsePathsToNodeIds translateBrowsePathsToNodeIds;
    UA_ExternalNodeStore_addReferences addReferences;
    UA_ExternalNodeStore_deleteReferences deleteReferences;
    UA_ExternalNodeStore_call call;
    UA_ExternalNodeStore_addOneWayReference addOneWayReference;
    UA_ExternalNodeStore_getOneWayReferences getOneWayReferences;
    UA_ExternalNodeStore_delete destroy;
} UA_ExternalNodeStore;

UA_StatusCode UA_EXPORT
UA_Server_addExternalNamespace(UA_Server *server, const UA_String *url,
                               UA_ExternalNodeStore *nodeStore, UA_UInt16 *assignedNamespaceIndex);

#ifdef __cplusplus
}
#endif

#endif /* UA_SERVER_EXTERNAL_NS_H_ */
