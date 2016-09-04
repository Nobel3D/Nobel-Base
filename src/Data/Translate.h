#pragma once
#include <def.h>
#include <Data/Array.h>
#include <Management/NException.h>

NL_NAMESTART

    template<typename Source, typename Destination>
    class Translate
    {
    private:
        index trs_iUsed               = 0;
        Array<Source> trs_tSrc        = nullptr;
        Array<Destination> trs_tDst   = nullptr;
    public:
        Translate(index size);
        ~Translate();

        void            Add(const Source& src, const Destination& dst);
        Destination&    FindBySource(const Source& src_key);
        Source&         FindByDestination(const Destination& dst_key);

        Destination& operator[](const Source& src_key);

    };

template<typename Source, typename Destination>
Translate<Source,Destination>::Translate(index size)
{

    if(size <= 0)
        throw NException("NTranslate::NTranslate(int size)","if(size <= 0)",
                         "trs_iSize cannot be lower than 0", "size="+NString::fromInt(size));

    trs_tSrc.New(size);
    trs_tDst.New(size);

}

template<typename Source, typename Destination>
Translate<Source,Destination>::~Translate()
{
    trs_tSrc.Delete();
    trs_tDst.Delete();
}

template<typename Source, typename Destination>
void Translate<Source,Destination>::Add(const Source& src, const Destination& dst)
{
    trs_tSrc[trs_iUsed] = Source(src);
    trs_tDst[trs_iUsed] = Destination(dst);
    trs_iUsed++;
}

template<typename Source, typename Destination>
Destination& Translate<Source,Destination>::FindBySource(const Source& src_key)
{
    int i = 0;
    while (i < trs_iUsed)
    {
        if (trs_tSrc[i] == src_key)
            return trs_tDst[i];
        i++;
    }
    throw NException("Destination& Translate<Source,Destination>::FindBySource(const Source& src_key)","while (i < trs_iUsed)",
                         "src_key not found in trs_tSrc");
}

template<typename Source, typename Destination>
Source& Translate<Source,Destination>::FindByDestination(const Destination& dst_key)
{
    int i = 0;
    while (i < trs_iUsed)
    {
        if (trs_tDst[i] == dst_key)
            return trs_tSrc[i];
        i++;
    }
    throw NException("Source& Translate::FindByDestination(const Source& dst_key)","while (i < trs_iUsed)",
                         "dst_key not found in trs_tDst");
}

template<typename Source, typename Destination>
Destination& Translate<Source,Destination>::operator[](const Source& src_key)
{
    return FindBySource(src_key);
}


NL_NAMECLOSE
