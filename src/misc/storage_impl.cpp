#include "storage.cpp"
#include "config.h"

bool StorageGlobal::storage_initialized = false;

template class Storage<Config>;
