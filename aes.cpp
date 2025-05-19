#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

/*
    Obtenemos la llave en partes de 8 bytes.
*/
string get_substr(string key, int begin) {

    return key.substr(begin, 8);

}
/*
    Realizamos la rotacion de palabras de izquierda.
*/
string rot_word(string key) {

    rotate(key.begin(), key.begin() + 2, key.end());

    return key;

} 
/*
    Hacemos un casteo de hex a entero.
*/
int hex_to_int(char index) {

    if(index >= '0' and index <= '9') return index - '0';
    else if(index >= 'a' and index <= 'f') return (index - 'a') + 10;
    
    return index;

}

uint8_t hex_string_to_uint8(string hex_str) {
 
    return static_cast<uint8_t>(stoi(hex_str, nullptr, 16));

}

vector<uint8_t> hex_string_to_bytes(string aux) {

    vector<uint8_t> bytes;

    for(size_t i = 0; i < aux.size(); i += 2) {

        bytes.push_back(hex_string_to_uint8(aux.substr(i, 2)));
    
    }
    
    return bytes;

}

vector<uint8_t> get_vector_in_bytes(vector<string> v) {

    vector<uint8_t> aux_bytes;
    
    for (auto hex_byte : v) {
    
        aux_bytes.push_back(hex_string_to_uint8(hex_byte));
    }

    return aux_bytes;

}

vector<string> get_vector_in_hex(vector<uint8_t> aux, vector<uint8_t> rcon) {
    
    vector<string> result_hex;

    for(size_t i = 0; i < aux.size(); i++) {
        
        uint8_t val = aux[i] ^ rcon[i];
        
        stringstream ss;
        
        ss << hex << setw(2) << setfill('0') << (int)val;
        
        result_hex.push_back(ss.str());
    
    }

    return result_hex;

}

vector<string> get_throught_sbox(string s, vector<vector<string>> sbox) {

    vector<string> aux;

    for(int i = 0; i < s.size(); i += 2) {

        string index = s.substr(i, 2);
        
        int fil = hex_to_int(index[0]);
        int col = hex_to_int(index[1]);

        aux.push_back(sbox[fil][col]);
        
    }

    return aux;

}

vector<string> get_gw3(string w3, vector<vector<string>> sbox, string rcon) {

    vector<string> aux = get_throught_sbox(w3, sbox);
    
    vector<uint8_t> aux_bytes = get_vector_in_bytes(aux);
    
    vector<uint8_t> rcon_bytes = hex_string_to_bytes(rcon);

    vector<string> result_hex = get_vector_in_hex(aux_bytes, rcon_bytes);

    return result_hex;

}

vector<string> get_key(string w, vector<string> w1) {

    vector<uint8_t> aux_w = hex_string_to_bytes(w);
    vector<uint8_t> aux_w1 = get_vector_in_bytes(w1);

    return get_vector_in_hex(aux_w, aux_w1);

}

string vector_to_string(vector<string> aux) {

    stringstream ss;

    for(string a : aux) ss << a;
    
    return ss.str();

}

vector<vector<string>> string_to_matriz(string v) {

    vector<vector<string>> state(4, vector<string>(4));

    for (size_t i = 0; i < 16; i++) {
        
        int row = i % 4;
        
        int col = i / 4;
        
        state[row][col] = v.substr(i * 2, 2);
    
    }

    return state;

}

string matriz_to_string(vector<vector<string>> state) {

    string result;
    
    for (size_t col = 0; col < 4; ++col) {
    
        for (size_t row = 0; row < 4; ++row) {
    
            result += state[row][col];
    
        }
   
    }

    return result;

}

string shift_rows(string v) {

    vector<vector<string>> state = string_to_matriz(v);

    for (size_t row = 1; row < 4; row++) {

        rotate(state[row].begin(), state[row].begin() + row, state[row].end());
    
    }

    string result = matriz_to_string(state);
    

    return result;
}

uint8_t mul(uint8_t a, uint8_t b) {
 
    uint8_t res = 0;
 
    while (b) {
 
        if (b & 1) res ^= a;
 
        bool high = a & 0x80;
 
        a <<= 1;
 
        if (high) a ^= 0x1b; 
 
        b >>= 1;
 
    }
 
    return res;
}

vector<vector<uint8_t>> uint8_to_matrix(string hex) {
    
    vector<vector<uint8_t>> matrix(4, vector<uint8_t>(4)); 

    for (size_t i = 0; i < 16; ++i) {
        
        string byte_str = hex.substr(i * 2, 2);
        uint8_t byte = stoi(byte_str, nullptr, 16);

        int col = i / 4;

        int row = i % 4;

        matrix[row][col] = byte;
    }

    return matrix;
}

string uint8_to_string(vector<vector<uint8_t>> m) {

    stringstream ss;
    for (size_t col = 0; col < 4; ++col) {
    
        for (size_t row = 0; row < 4; ++row) {
            
            ss << hex << setw(2) << setfill('0') << static_cast<int> (m[row][col]);
        
        }
    
    }

    return ss.str();

}

string mix_column(string k) {

    vector<vector<uint8_t>> state = uint8_to_matrix(k);
    vector<vector<uint8_t>> mix_matriz = {
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    };

    vector<vector<uint8_t>> result(4, vector<uint8_t>(4));

    for (size_t col = 0; col < 4; col++) {
     
        for (size_t row = 0; row < 4; row++) {
     
            uint8_t value = 0;
     
            for (size_t k = 0; k < 4; k++) {
     
                value ^= mul(mix_matriz[row][k], state[k][col]);
     
            }
     
            result[row][col] = value;
            
        }

    }

    return uint8_to_string(result);

}

string round_0(string key, string plain_text, vector<vector<string>> sbox) {

    vector<uint8_t> aux_key = hex_string_to_bytes(key);
    
    vector<uint8_t> aux_plain_text = hex_string_to_bytes(plain_text);
    
    string v = vector_to_string(get_vector_in_hex(aux_key, aux_plain_text));

    return mix_column(shift_rows(vector_to_string(get_throught_sbox(v, sbox))));

}

string round_1(string key, string plain_text, vector<vector<string>> sbox) {
    
    vector<uint8_t> aux_key = hex_string_to_bytes(key);
    
    vector<uint8_t> aux_plain_text = hex_string_to_bytes(plain_text);
    
    return vector_to_string(get_vector_in_hex(aux_key, aux_plain_text));

}

void all_round_plain_text(string key, string plain_text, vector<vector<string>> sbox,
    vector<vector<string>> round) {
 
    cout << "Round 0 " << round_0(key, plain_text, sbox) << '\n';

    string round0 = round_0(key, plain_text, sbox);

    for(size_t i = 1; i < 9; i++) {

        string round11 = vector_to_string(round.at(i - 1));
        
        string round_2 = mix_column(shift_rows(vector_to_string(get_throught_sbox(round_1(round0, round11, sbox), sbox))));

        cout << "Round " << i + 1 << " " << vector_to_string(get_throught_sbox(round_1(round0, round11, sbox), sbox)) << '\n';
    
        round0 = round_2;

    }

    string round_9 =  shift_rows(vector_to_string(get_throught_sbox(round_1(round0, vector_to_string(round.at(8)), sbox), sbox)));

    cout << "Round 10 " << round_1(round_9, vector_to_string(round.at(9)), sbox) << '\n';



}

void all_round_key(vector<vector<string>> sbox, string key, int n, vector<vector<string>>& round) {

    cout << "\nRound " << n - 1 << " Key: " << key << '\n';

    if(n <= 10) {

        string w0 = get_substr(key, 0);
        string w1 = get_substr(key, 8);
        string w2 = get_substr(key, 16);
        string w3_aux = get_substr(key, 24);
        string w3 = rot_word(w3_aux);

        string key_temp = key;

        vector<string> rcon_values = {
            "01000000", "02000000", "04000000", "08000000", "10000000",
            "20000000", "40000000", "80000000", "1b000000", "36000000"
        };

        vector<string> gw3 = get_gw3(w3, sbox, rcon_values[n - 1]);

        vector<string> w4 = get_key(w0, gw3);
        vector<string> w5 = get_key(w1, w4);
        vector<string> w6 = get_key(w2, w5);
        vector<string> w7 = get_key(w3_aux, w6);

        vector<string> result;

        result.insert(result.end(), w4.begin(), w4.end());
        result.insert(result.end(), w5.begin(), w5.end());
        result.insert(result.end(), w6.begin(), w6.end());
        result.insert(result.end(), w7.begin(), w7.end());

        key = vector_to_string(result);

        round[n - 1].push_back(key);

        all_round_key(sbox, key, n + 1, round);

    }

    cout << '\n';

}

int main() {

    vector<vector<string>> sbox = {
        {"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
        {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
        {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
        {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
        {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
        {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
        {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
        {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
        {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
        {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
        {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
        {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
        {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
        {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
        {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
        {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}
    };

    string key = "5468617473206d79204b756e67204675";
    string plain_text = "54776f204f6e65204e696e652054776f";
 
    vector<vector<string>> round(10);

    all_round_key(sbox, key, 1, round);
 
    all_round_plain_text(key, plain_text, sbox, round);

    return 0;

}