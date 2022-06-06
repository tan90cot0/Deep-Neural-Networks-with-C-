#ifndef libaudio_API
#define libaudio_API

typedef struct{
    int label;
    float prob;
}pred_t;


extern pred_t* libaudioAPI(const char*, pred_t*);

#endif    
