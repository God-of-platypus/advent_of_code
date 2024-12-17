#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

// Define the registers
u_int64_t A, B, C;

// Function to get the value of a combo operand
u_int64_t getComboValue(u_int64_t operand) {
    if (operand <= 3) return operand; // 0-3: literal values
    if (operand == 4) return A;       // 4: value of A
    if (operand == 5) return B;       // 5: value of B
    if (operand == 6) return C;       // 6: value of C
    return 0; // 7 is reserved; won't appear in valid programs
}


u_int64_t getComboValue(const u_int64_t operand, const u_int64_t A, const u_int64_t B, const u_int64_t C) {
    if (operand <= 3) return operand; // 0-3: literal values
    if (operand == 4) return A;       // 4: value of register A
    if (operand == 5) return B;       // 5: value of register B
    if (operand == 6) return C;       // 6: value of register C
    return 0; // Reserved value (7)
}

bool runProgram(const vector<u_int64_t>& program, const u_int64_t A_initial, vector<u_int64_t>& output) {
    u_int64_t A = A_initial, B = 0, C = 0; // Initialize registers
    u_int64_t ip = 0; // Instruction pointer
    const u_int64_t programSize = program.size();

    while (ip < programSize) {
        u_int64_t opcode = program[ip];      // Fetch opcode
        u_int64_t operand = program[ip + 1]; // Fetch operand

        switch (opcode) {
            case 0: { // adv: A = A / (2^operand)
                int divisor = 1 << getComboValue(operand, A, B, C);
                if (divisor == 0) return false; // Prevent division by zero
                A /= divisor;
                break;
            }
            case 1: { // bxl: B = B XOR operand
                B ^= operand;
                break;
            }
            case 2: { // bst: B = operand % 8
                B = getComboValue(operand, A, B, C) % 8;
                break;
            }
            case 3: { // jnz: if A != 0, jump to operand
                if (A != 0) {
                    ip = operand;
                    continue; // Jump directly to operand
                }
                break;
            }
            case 4: { // bxc: B = B XOR C
                B ^= C;
                break;
            }
            case 5: { // out: output (operand % 8)
                output.push_back(getComboValue(operand, A, B, C) % 8);
                break;
            }
            case 6: { // bdv: B = A / (2^operand)
                int divisor = 1 << getComboValue(operand, A, B, C);
                if (divisor == 0) return false;
                B = A / divisor;
                break;
            }
            case 7: { // cdv: C = A / (2^operand)
                int divisor = 1 << getComboValue(operand, A, B, C);
                if (divisor == 0) return false;
                C = A / divisor;
                break;
            }
            default: {
                return false; // Invalid opcode
            }
        }

        ip += 2; // Move to the next instruction
    }
    return true;
}


// Function to simulate the 3-bit computer
void runProgram(const vector<u_int64_t>& program) {
    vector<u_int64_t> output; // To store output values
    u_int64_t ip = 0;         // Instruction pointer starts at 0
    u_int64_t programSize = program.size();

    while (ip < programSize) {
        u_int64_t opcode = program[ip];      // Fetch the opcode
        u_int64_t operand = program[ip + 1]; // Fetch the operand

        switch (opcode) {
            case 0: { // adv: A = A / (2^operand)
                int divisor = 1 << getComboValue(operand); // 2^operand
                A /= divisor;
                break;
            }
            case 1: { // bxl: B = B XOR operand (literal)
                B ^= operand;
                break;
            }
            case 2: { // bst: B = operand % 8
                B = getComboValue(operand) % 8;
                break;
            }
            case 3: { // jnz: if (A != 0) jump to operand
                if (A != 0) {
                    ip = operand;
                    continue; // Skip the normal IP increment
                }
                break;
            }
            case 4: { // bxc: B = B XOR C (operand ignored)
                B ^= C;
                break;
            }
            case 5: { // out: Output (operand % 8)
                output.push_back(getComboValue(operand) % 8);
                break;
            }
            case 6: { // bdv: B = A / (2^operand)
                int divisor = 1 << getComboValue(operand);
                B = A / divisor;
                break;
            }
            case 7: { // cdv: C = A / (2^operand)
                int divisor = 1 << getComboValue(operand);
                C = A / divisor;
                break;
            }
            default: {
                cerr << "Invalid opcode encountered: " << opcode << endl;
                return;
            }
        }

        ip += 2; // Move to the next instruction
    }

    // Print the output as a comma-separated string
    for (size_t i = 0; i < output.size(); ++i) {
        if (i > 0) cout << ",";
        cout << output[i];
    }
    cout << endl;
}

// Function to parse the input file
void parseInputFile(const string& filename, vector<u_int64_t>& program) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file: " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.find("Register A:") != string::npos) {
            A = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Register B:") != string::npos) {
            B = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Register C:") != string::npos) {
            C = stoi(line.substr(line.find(':') + 1));
        } else if (line.find("Program:") != string::npos) {
            string programData = line.substr(line.find(':') + 1);
            stringstream ss(programData);
            int instruction;
            while (ss >> instruction) {
                program.push_back(instruction);
                if (ss.peek() == ',') ss.ignore();
            }
        }
    }

    inputFile.close();
}

u_int64_t findLowestA(const vector<u_int64_t>& program) {
    queue<pair<u_int64_t, int>> q;
    q.push({0, 0});
    uint64_t min = ~0;
    while (!q.empty()) {
        auto [value, depth] = q.front();
        q.pop();

        vector<u_int64_t> candidate;
        uint64_t div8 = value / 8;
        for (uint64_t i = value; i / 8 == div8; ++i) {
            vector<u_int64_t> output;
            runProgram(program, i, output);
            bool sliced = true;
            if (output == program) {
                return i;
            }
            for (int j = 0; j < output.size(); ++j) {
                if (output[j] != program[program.size() + j - 1 - depth]) {
                    sliced = false;
                }
            }
            if (sliced) {
                candidate.push_back(i);
            }
        }

        for (auto t: candidate) {
            q.push({8 * t, depth + 1});
        }
    }
    return 0;
}

int main() {
    // Input file path
    string filename = "input.txt";

    // Program instructions
    vector<u_int64_t> program;

    // Parse the input file
    parseInputFile(filename, program);

    // Run the program
    runProgram(program);



    u_int64_t result = findLowestA(program);

    cout << result << endl;

    return 0;
}
