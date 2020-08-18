#include "SampleAddIn.h"

Component::LibraryMeta::LibraryMeta() {
    AddComponent(u"Sample", SampleAddIn::create);
    AddComponent(u"SampleAlias", SampleAddIn::create);
}
