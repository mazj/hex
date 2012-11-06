void
memset16(uint16_t *dst, uint16_t value, size_t size)
{
  size >>= 1;
  while(size--) {
    *dst++ = value;
  }
}

void
memset32(uint32_t *dst, uint32_t value, size_t size)
{
  size >>= 2;
  while(size--) {
    *dst++ = value;
  }
}