# gmsv_standard_win64
> [!WARNING]  
> This binary module development is still in progress, and potential security risks need to be considered.
# Features
* filesystem
    * `bool` Exists( `string` filePath ) - Returns boolean of whether the file or directory exists or not.
    * `bool` IsDirectory( `string` filePath ) - Returns whether the given file is directory or not.
    * `bool` IsEmpty( `string` filePath ) - Returns whether the given file or directory is empty or not.
    * `bool` CreateDirectory( `string` filePath ) - Creates directory that is relative to the GarrysMod folder.
    * `bool` CopyDirectory( `string` filePath, `string` newPath, `number` copyOptions = 0 ) - Copies directory with given path. Third argument is optional, accepts copy_options flags.
    * `bool` CopyFile( `string` filePath, `string` newPath ) - Copies file with given path.
    * `bool` Remove( `string` filePath ) - Removes file or directory with given path.
    * `bool` Rename( `string` filePath, `string` newPath ) - Renames file or directory with given string.
    * `bool` Resize( `string` filePath, `number` nBytes ) - Alter given file size.
    * `number` GetSize( `string` filePath ) - Returns the files size in bytes.
    * `number` GetTime( `string` filePath ) - Returns when the file or folder was last modified in Unix time.
    * `table` Iterate( `string` filePath, `bool` recursive = false ) - Returns directory contents as table. Second argument is optional, set to true to enable recursive mode.
* filestream
    * `bool`, `string`, `number` Read( `string` filePath ) - Returns stream state, content of file, stream size.
    * `bool`, `number` Write( `string` filePath, `string` content ) - Writes given string to file.
    * `number` GetSize( `string` filePath ) - Returns files size in bytes or -1 if file is not found.
    * `bool` IsGood( `string` filePath ) - Returns file stream state.
