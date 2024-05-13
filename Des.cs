using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SecurityLibrary.DES
{
    /// <summary>
    /// If the string starts with 0x.... then it's Hexadecimal not string
    /// </summary>
    public class DES : CryptographicTechnique
    {
        readonly int[,] PC_1 = new int[8, 7] {
                { 57, 49, 41, 33, 25, 17, 9 },
                { 1, 58, 50, 42, 34, 26, 18 },
                { 10, 2, 59, 51, 43, 35, 27 },
                { 19, 11, 3, 60, 52, 44, 36 },
                { 63, 55, 47, 39, 31, 23, 15 },
                { 7, 62, 54, 46, 38, 30, 22 },
                { 14, 6, 61, 53, 45, 37, 29 },
                { 21, 13, 5, 28, 20, 12, 4 } };
        readonly int[,] PC_2 = new int[8, 6] {
                { 14, 17, 11, 24, 1, 5 },
                { 3, 28, 15, 6, 21, 10 },
                { 23, 19, 12, 4, 26, 8 },
                { 16, 7, 27, 20, 13, 2 },
                { 41, 52, 31, 37, 47, 55 },
                { 30, 40, 51, 45, 33, 48 },
                { 44, 49, 39, 56, 34, 53 },
                { 46, 42, 50, 36, 29, 32 } };
        readonly int[,] P = new int[8, 4] {
                { 16, 7, 20, 21 },
                { 29, 12, 28, 17 },
                { 1, 15, 23, 26 },
                { 5, 18, 31, 10 },
                { 2, 8, 24, 14 },
                { 32, 27, 3, 9 },
                { 19, 13, 30, 6 },
                { 22, 11, 4, 25 } };
        readonly int[,] EB = new int[8, 6] {
                { 32, 1, 2, 3, 4, 5 },
                { 4, 5, 6, 7, 8, 9  },
                { 8, 9, 10, 11, 12, 13 },
                { 12, 13, 14, 15, 16, 17 },
                { 16, 17, 18, 19, 20, 21 },
                { 20, 21, 22, 23, 24, 25 },
                { 24, 25, 26, 27, 28, 29 },
                { 28, 29, 30, 31, 32, 1  } };
        readonly int[,] IP = new int[8, 8] {
                { 58, 50, 42, 34, 26, 18, 10, 2 },
                { 60, 52, 44, 36, 28, 20, 12, 4 },
                { 62, 54, 46, 38, 30, 22, 14, 6 },
                { 64, 56, 48, 40, 32, 24, 16, 8 },
                { 57, 49, 41, 33, 25, 17, 9, 1  },
                { 59, 51, 43, 35, 27, 19, 11, 3 },
                { 61, 53, 45, 37, 29, 21, 13, 5 },
                { 63, 55, 47, 39, 31, 23, 15, 7 } };
        readonly int[,] IP_1 = new int[8, 8] {
                { 40, 8, 48, 16, 56, 24, 64, 32 },
                { 39, 7, 47, 15, 55, 23, 63, 31 },
                { 38, 6, 46, 14, 54, 22, 62, 30 },
                { 37, 5, 45, 13, 53, 21, 61, 29 },
                { 36, 4, 44, 12, 52, 20, 60, 28 },
                { 35, 3, 43, 11, 51, 19, 59, 27 },
                { 34, 2, 42, 10, 50, 18, 58, 26 },
                { 33, 1, 41, 9, 49, 17, 57, 25  } };

        int[,,] SBoxes = new int[8, 4, 16]
         {
            {
               { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
               { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
               { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
               { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
            },
            {
                { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
                { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
                { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
                { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
            },
            {
                { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
                { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
                { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
                { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
            },
            {
                { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
                { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
                { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
                { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
            },
            {
               { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
               { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
               { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
               { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
            },
            {
               { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
               { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
               { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
               { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
            },
            {
                { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
                { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
                { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
                { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
            },
            {
                { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
                { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
                { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
                { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
            }
        };

        //helper functions
        // DES : Data Encryption Standered 
        // Symmetric : key of Enc = Key of Dec
        // Block cipher: process P.T block by (-)block slower than stream cipher 
        public string Permute(int[,] table, string input)
        {
            var sb = new StringBuilder();
            foreach (int position in table)
            {
                sb.Append(input[position - 1]); 
            }
            return sb.ToString();
        }

        public string LeftShift(string input, int amount)
        {
            // input = "abcdefgh" , amount (3)
            return input.Substring(amount) + input.Substring(0, amount);
        }

        public List<string> GenerateRoundKeys(string key56)
        {
            // the input is one key 
            // but in DES we need 16 diffrent key
            // this function to generate keys for each round
            string C0 = key56.Substring(0, 28);
            string D0 = key56.Substring(28);
            var roundKeys = new List<string>();
            var shiftAmounts = new int[] { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

            for (int i = 0; i < 16; i++)
            {
                C0 = LeftShift(C0, shiftAmounts[i]);
                D0 = LeftShift(D0, shiftAmounts[i]);
                // each round key of 48 bit
                roundKeys.Add(Permute(PC_2, C0 + D0));
            }
            return roundKeys;
        }

        public string SBox(string input)
        {
            // take expanded 48 bit and retrun 32 bit
            // we have 8 s-boxes
            // each take 6 bits and convert them to 4 bits
            var sb = new StringBuilder();
            for (int i = 0; i < 8; i++)
            {
                string block = input.Substring(i * 6, 6);// convert the input to 6 bit block
                int row = Convert.ToInt32(block[0].ToString() + block[5], 2);
                int col = Convert.ToInt32(block.Substring(1, 4), 2);
                int sBoxValue = SBoxes[i, row, col];
                sb.Append(Convert.ToString(sBoxValue, 2).PadLeft(4, '0'));
            }
            return sb.ToString();
        }
        public string Xor(string a, string b)
        {
            var sb = new StringBuilder();
            for (int i = 0; i < a.Length; i++)
            {
                sb.Append((a[i] ^ b[i]).ToString());
            }
            return sb.ToString();
        }
        public string RoundFunction(string right, string roundKey)
        {
            // make confusion by (substitution): No relationship between C.T and P.T
            // make difusion by (Permutation):change P.T bit affect mant C.T bits
            // avalanche effect like difusion
            // strict analanche effect : chamge on bit --> change 1/2 of P.T
            // WE HAVE STRONG AVALANCHE EFFECT IN DES
            string expandedRight = Permute(EB, right);// expanded to 48 bit so that i can take xor
            string xored = Xor(expandedRight, roundKey);
            string sBoxOutput = SBox(xored); // reduce the 48 bit to 32 bit
            return Permute(P, sBoxOutput);
        }
        public override string Encrypt(string plainText, string key)
        {
            //This line of code converts a hexadecimal string representation of a key into a binary string representation with a fixed length of 64 bits
            //padded with zeroes to make it exactly 64 bits long
            string key64 = Convert.ToString(Convert.ToInt64(key, 16), 2).PadLeft(64, '0');
            List<string> key1Shifted = new List<string>();
            List<string> key2Shifted = new List<string>();

            string key56 = Permute(PC_1, key64);

            string key1_28 = key56.Substring(0, 28);
            string key2_28 = key56.Substring(28);

            for (int i = 0; i < 16; i++)
            {
                int shiftAmount = (i == 0 || i == 1 || i == 8 || i == 15) ? 1 : 2;
                key1_28 = LeftShift(key1_28, shiftAmount);
                key2_28 = LeftShift(key2_28, shiftAmount);
                key1Shifted.Add(key1_28);
                key2Shifted.Add(key2_28);
            }

            List<string> roundKeys = new List<string>();
            for (int i = 0; i < 16; i++)
            {
                string combinedKey = key1Shifted[i] + key2Shifted[i];
                roundKeys.Add(Permute(PC_2, combinedKey));
            }
            
            string plain64 = Convert.ToString(Convert.ToInt64(plainText, 16), 2).PadLeft(64, '0');
            string permutedPlaintext = Permute(IP, plain64);

            string leftHalf = permutedPlaintext.Substring(0, 32);
            string rightHalf = permutedPlaintext.Substring(32);

            for (int i = 0; i < 16; i++)
            {
                string temp = rightHalf;
                rightHalf = RoundFunction(rightHalf, roundKeys[i]);
                rightHalf = Xor(rightHalf, leftHalf);
                leftHalf = temp;
            }

            string combinedHalves = rightHalf + leftHalf;
            string ciphertext = Permute(IP_1, combinedHalves);
            return "0x" + Convert.ToInt64(ciphertext, 2).ToString("X");
        }
        public override string Decrypt(string cipherText, string key)
        {
            // THE ROUNDS FIXED BUT 
            string key64 = Convert.ToString(Convert.ToInt64(key, 16), 2).PadLeft(64, '0');
            string key56 = Permute(PC_1, key64);
            var roundKeys = GenerateRoundKeys(key56);
            roundKeys.Reverse(); // THE ORDER ROUND KEYS WILL BE REVERSED


            string cipher64 = Convert.ToString(Convert.ToInt64(cipherText, 16), 2).PadLeft(64, '0');
            string permutedCipher = Permute(IP, cipher64);

            string left = permutedCipher.Substring(0, 32);
            string right = permutedCipher.Substring(32, 32);

            for (int i = 0; i < 16; i++)
            {
                string temp = left;
                left = right; 
                right = Xor(temp, RoundFunction(right, roundKeys[i]));
            }

            string combined = right + left;
            string plainText64 = Permute(IP_1, combined);
            //This line of code converts a binary string representation of ciphertext into a hexadecimal string 
            return "0x" + Convert.ToInt64(plainText64, 2).ToString("X").PadLeft(16, '0');
        }
    }
}
// we can BREACK DES IN 3 DAYS BY USING SUPER COMPUTER
// SO WE USED Double DES , Triple DES instead
