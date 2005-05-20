
//
// CVS Log Info for $RCSfile: VirtualFileSystem.h,v $
//
// $Id: VirtualFileSystem.h,v 1.1 2005/05/10 16:42:32 davrieb Exp $
// $Log$
//

#ifndef VirtualFileSystem_h__
#define VirtualFileSystem_h__

#include "types.h"
#include "kmalloc.h"

/// File system flag indicating if the system in question requires an device.
#define FS_REQUIRES_DEV   0x0001

/// The maximal number of file system types.
#define MAX_FILE_SYSTEM_TYPES 16

class Superblock;

class FileSystemType
{
public:

  typedef Superblock *(*ReadSuper) (struct Superblock *, void *, int32);

protected:

  const char* fs_name_;

  int32 fs_flags_;

//  Superblock *(*readsuper) (struct Superblock *, void *, int32);
  ReadSuper read_super_;


public:

  FileSystemType();

  FileSystemType(const char* fs_name);

  ~FileSystemType();

  const char* getFSName() const;

  void setFSName(const char* fs_name);

  int32 getFSFlags() const;

  void setFSFlags(int32 fs_flags);

  const ReadSuper getReadSuperFunction() const;

  void setReadSuperFunction(ReadSuper read_super);

};

class VirtualFileSystem
{
protected:

  Superblock *superblock_;

  /// A null-terminated array of file system types.
  FileSystemType *file_system_types_;

public:

  int32 registerFileSystem(FileSystemType *file_system_type);

  int32 unregisterFileSystem(FileSystemType *file_system_type);


};

#endif