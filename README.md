# KVS-Simple
Table de hashage implémenté avec murmurhash3 x64 128bits

void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out);

out sera l'index dans le table de hashage !

!! Ce teste présente une erreur au niveau des types uint32 , int
