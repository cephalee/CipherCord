#include "../include/header.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

int get_file_id(char *fname){
    int length = sizeof(EXTENSIONS_MAP) / sizeof(EXTENSIONS_MAP[0]);
    char *ext = strrchr(fname, '.');
    if(ext){
        for(int i = 0; i < length; i++){
            if(!strcmp(EXTENSIONS_MAP[i], ext)){
                return i;
            }
        }
    }
    return 0;
}

unsigned get_file_size(FILE *file){
    fseek(file, 0, SEEK_END);
    unsigned size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

void write_header(char *fname, FILE *file, file_header *fheader){
    fheader->id = get_file_id(fname);
    fheader->size = get_file_size(file);
}