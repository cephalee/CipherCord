#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct __attribute__((packed)){
    uint32_t id;
    uint64_t size;
    char iv[16];

}file_header;

int get_file_id(char *fname);
unsigned get_file_size(FILE *file);

const char* EXTENSIONS_MAP[] = {
    "unknown",
    ".png", ".jpg", ".jpeg", ".gif", ".bmp", ".webp", ".tiff", ".svg", ".ico", ".raw",
    ".pdf", ".docx", ".doc", ".txt", ".rtf", ".odt", ".xlsx", ".csv", ".pptx", ".epub",
    ".zip", ".rar", ".7z", ".tar", ".gz", ".iso", ".bz2", ".xz", ".zst", ".lz",
    ".mp3", ".wav", ".flac", ".ogg", ".m4a", ".wma", ".aac", ".aiff", ".opus", ".mid",
    ".mp4", ".mkv", ".avi", ".mov", ".wmv", ".flv", ".webm", ".m4v", ".mpg", ".3gp",
    ".exe", ".msi", ".bin", ".elf", ".so", ".dll", ".deb", ".rpm", ".appimage", ".sh",
    ".c", ".cpp", ".h", ".py", ".js", ".html", ".css", ".java", ".php", ".go", ".rs",
    ".psd", ".ai", ".blend", ".obj", ".stl", ".fbx", ".unitypackage", ".uasset",
    ".json", ".xml", ".sql", ".sqlite", ".db", ".yaml", ".yml", ".ini", ".log"
};

#endif

