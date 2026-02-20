#define POCKETLZMA_LZMA_C_DEFINE
#include <base/archive/pocketlzma.hpp>
#include "game.hpp"
using namespace std;

vector<u8> ReadLZMAArchive(string path) {
    vector<u8> data;
    vector<u8> decompressedData;
    plz::FileStatus fileStatus = plz::File::FromFile(path, data);
    
    if (fileStatus.status() == plz::FileStatus::Code::Ok) {
        plz::PocketLzma p;
        plz::StatusCode status = p.decompress(data, decompressedData);
        if (status == plz::StatusCode::Ok) {
            return decompressedData;
        }
    }
    exit(1);
    return data;
}

U8Data getResourceFromU8(vector<u8> &u8Arc, string resource) {
    std::stringstream ss;
    // weirdly i have to sign the data
    ss.write((char*)u8Arc.data(), u8Arc.size());

    // Okay so now it's in the STREAMER
    U8_archive_header header;
    U8_node* nodes;
    u32 num_nodes;
    U8_node root_node;
    u8* string_table;

    ss.read((char*)&header, sizeof(header));
    if (little32(header.tag) != 0x55AA382D) {
        cout << "Error occured: Tried to extract data from invaild archive." << endl;
        cout << "Aborted" << endl;
    }

    ss.read((char*)&root_node, sizeof(U8_node));
    num_nodes = little32(root_node.size) - 1;
    //cout << "ARChive opened. Number of files: " << num_nodes << endl;

    // Num_nodes is already little endian
    nodes = new U8_node[num_nodes];
    ss.read((char*)nodes, num_nodes*sizeof(U8_node));

    u32 data_offset = little32(header.data_offset);
    // AWESOME math
    size_t rest_size = data_offset - sizeof(header) - (num_nodes+1)*sizeof(U8_node);

    string_table = new u8[rest_size];
    ss.read((char*)string_table, rest_size);

    u16 dir_stack[6];
    int dir_index = 0;

    vector<string> path;

    for (u32 i = 0; i < num_nodes; i++) {
        U8_node* node = &nodes[i];
        u16 type = little16(node->type);
        u16 name_offset = little16(node->name_offset);
        u32 my_data_offset = little32(node->data_offset);
        u32 size = little32(node->size);
        char* name = (char*)&string_table[name_offset];
        
        // Ok so we need to get the file.
        // yeah anyway

        if (type == 0x0100) {
            // directory
            dir_stack[++dir_index] = size;
            
            // Add a slash for the path
            char* nameAndSlash = new char[sizeof(name)+1];
            sprintf(nameAndSlash, "%s/", name);
            // Add to path
            path.push_back(nameAndSlash);

            // Okay.
            delete[] nameAndSlash;
        }
        else {
            // File, probs
            if (type != 0x0000) {
                cout << "Error occured: Corrupt archive" << endl;
            }
            // Add to path
            path.push_back(name);

            string FullPath;

            for (string &s : path) {
                FullPath += s;
            }
            // Check if we have to right file. If so, ship it!
            // Remember "resource"? It's the path provided in the args
            if (resource == FullPath) {
                ss.seekg(my_data_offset, ios::beg);
                void* data = malloc(size);
                ss.read((char*)data, size);

                U8Data ret;
                ret.data = data;
                ret.size = size;
                delete[] string_table;
                delete[] nodes;
                return ret;
            }

            // Remove before everything gets super corrupted
            path.pop_back();
        }

        while (dir_stack[dir_index] == i+2 && dir_index > 0) {
            dir_index--;
            // Since we're no longer in this directory we can remove it from the path
            path.pop_back();
        }
    }
    //Ok so free these
    delete[] string_table;
    delete[] nodes;
    cout << "getResourceFromU8(): Could not find file " << resource << " under ./ in the archive." << endl;
    // return nothing
    U8Data ret;
    ret.data = NULL;
    ret.size = 0;
    return ret;
}

ofImage loadImageFromU8(vector<u8> &arc, string resource) {
    ofImage ret;

    U8Data imageData = getResourceFromU8(arc, resource);
    ofBuffer buf = ofBuffer((char*)imageData.data, imageData.size);
    // load it
    ret.load(buf);

    // now that we've copied it to a ofBuffer we can kill it
    free(imageData.data);

    return ret;
}
