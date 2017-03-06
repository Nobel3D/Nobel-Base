#pragma once

#include <def.h>
#include <Data/Array.h>
#include <Management/NException.h>

NL_NAMESTART

    template<typename Source, typename Destination>
    class Translate
    {
    private:
         INDEX iUsed = 0;
         Array<Source>* tSrc = nullptr;
         Array<Destination>* tDst = nullptr;
    public:
        Translate(INDEX _index);
        ~Translate();

        void            Add(const Source& src, const Destination& dst);
        Destination&    FindBySource(const Source& src_key);
        Source&         FindByDestination(const Destination& dst_key);

        Destination& operator[](const Source& src_key);
    };

template<typename Source, typename Destination>
Translate<Source,Destination>::Translate(INDEX _index)
{

    tSrc = new Array<Source>(_index);
    tDst = new Array<Destination>(_index);

}

template<typename Source, typename Destination>
Translate<Source,Destination>::~Translate()
{
    delete[] tSrc;
    delete[] tDst;
}

template<typename Source, typename Destination>
void Translate<Source,Destination>::Add(const Source& src, const Destination& dst)
{
    (*tSrc)[iUsed] = Source(src);
    (*tDst)[iUsed] = Destination(dst);
    iUsed++;
}

template<typename Source, typename Destination>
Destination& Translate<Source,Destination>::FindBySource(const Source& src_key)
{
    int i = 0;
    while (i < iUsed)
    {
        if ((*tSrc)[i] == src_key)
            return (*tDst)[i];
        i++;
    }
    throw NException("Destination& Translate<Source,Destination>::FindBySource(const Destination& src_key)","while (i < iUsed)",
                         "src_key not found in tSrc");
}

template<typename Source, typename Destination>
Source& Translate<Source,Destination>::FindByDestination(const Destination& dst_key)
{
    int i = 0;
    while (i < iUsed)
    {
        if ((*tDst)[i] == dst_key)
            return (*tSrc)[i];
        i++;
    }
    throw NException("Source& Translate::FindByDestination(const Source& dst_key)","while (i < iUsed)",
                         "dst_key not found in tDst");
}

template<typename Source, typename Destination>
Destination& Translate<Source,Destination>::operator[](const Source& src_key)
{
    return FindBySource(src_key);
}


NL_NAMECLOSE
