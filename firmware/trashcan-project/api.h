#ifndef API_H
#define API_H

typedef bool boolean;

#define DISABLE_COPY(Class)      \
  Class(const Class &) = delete; \
  Class operator=(const Class &) = delete

#endif  // API_H