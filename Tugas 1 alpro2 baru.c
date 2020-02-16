#include <stdio.h>
#include <conio.h>
#include <string.h>
FILE *newFile; //newFile buat akses file
char namaFile[100]; //namaFile buat menyimpan nama file
char removeFile[100]; //removeFile buat menyimpan nama file yang akan diremove
char masukFile[100]; //masukFile buat menyimpan kalimat yang akan dimasukan
char keluarFile[100]; //keluarFile buat menyimpan kalimat yang dari file (mau di output)
int cek,p,del,size; //p buat menu, del buat status delete(kedelete apa engga), size buat ukuran file

void buatFile(){
	printf("Masukan nama file : "); //output
	fflush(stdin); // buat ngebersihin buffer (ga ngerti aku juga tapi kalau gaada ini fungsi gets dibawah error mulu)
	gets(namaFile); // get string (buat input string / kalimat)
	strcat(namaFile,".txt"); // string concat buat menggabungkan namaFile yang diinput dengan ekstensinya yaitu .txt
	newFile = fopen(namaFile,"r"); //akses file dengan kode akses read (r)
	if(newFile != NULL){ //jika file yang diakses sudah ada
		printf("File tersebut sudah ada"); //output
//					memset(namaFile,0,strlen(namaFile));
	}else{ //selain itu
		newFile = fopen(namaFile,"w");//akses file dengan kode akses write (w)
		if(newFile != NULL){ //jika file tersebut sudah menjadi ada (asalnya kosong)
			printf("File %s telah dibuat !!\n",namaFile); //output
		}else{ //selain itu
			printf("File %s tidak bisa dibuat !!\n"); //output
		}
	}
	fclose(newFile); //tutup akses file
}

int cekFile(char nama[100]){
	int status;
	newFile = fopen(nama,"r");
	if(newFile == NULL){
		status = 0;
	}else{
		status = 1;
	}
	fclose(newFile);
	return status;
}

void tambahFile(){
	cek = cekFile(namaFile);
	if (cek == 0){ // jika file yang diakses tidak ada
		printf("Maaf anda harus membuat file terlebih dahulu !!");
	}else{ //selain itu
		printf("Masukan Kata atau Kalimat : "); //output
		fflush(stdin); //ngebersihin buffer (ga ngerti aku juga hehe)
		gets(masukFile); //get string (buat input string)
		newFile = fopen(namaFile,"a"); //akses file dengan kode akses "a" (append)
		fprintf(newFile,"%s",masukFile); //input file ke newFile(yang diakses diatas) dengan tipe %s(string) isi kalimatnya ada divariable masukFile
		printf("Kata atau Kalimat %s berhasil dimasukkan !!\n",masukFile); //Output berhasil
		fclose(newFile);//tutup akses file
	}
}

void tampilFile(){
	cek = cekFile(namaFile);
	if(cek == 0){ //jika file yang diakses tidak ada
		printf("Maaf anda harus membuat file terlebih dahulu !!"); //output
	}else{
		fgets(keluarFile,100,newFile); // fgets untuk menyimpan isi file yang diakses newFile kedalam variable keluarFile dengan maksimal karakter 100
		fseek(newFile, 0, SEEK_END); // fseek untuk menetapkan posisi file yang diakses newFile dengan offset 0
		size = ftell(newFile); // ftell untuk menentukan file pointer yang diakses newFile (dengan fseek digabung untuk menentukan ukuran file
		if(size == 0){ //jika ukuran file 0
			printf("Maaf isi file masih kosong"); //output
		}else{ //selain itu
			printf("Kata atau kalimat yang tertulis dalam file adalah : %s\n",keluarFile); //output
		}
	}
}

void hapusFile(){
	cek = cekFile(namaFile);
	if(newFile == NULL){ //jika file yang diakses kosong
		printf("Maaf anda harus membuat file terlebih dahulu !!"); //output
	}else{
		del = remove(namaFile); //meremove file dengan nama namaFile dan memberikan status(berhasil atau tidak) kedalam variable del (ini masih error entah kenapa T_T status yang dihasilkan -1 (artinya error))
		if (del == 0){ //jika status(del) = 0 (berhasil)
			printf("File %s telah dihapus !! \n",namaFile);//output
		}else{ //selain itu (status(del) bukan 0)
			perror("File tidak bisa dihapus / tidak ada !!\n"); //output
		}
	}
}

void tampilMenu(){
	printf("Pilih Salah satu menu dibawah :\n"); //menuuuu
	printf("1. Buat File teks\n");
	printf("2. Tambahkan data file\n");
	printf("3. Tampilkan data file\n");
	printf("4. Hapus file teks\n");
	printf("5. exit\n\n");
}

int main(){
	do{ // repeat menu
		system("cls"); //clear screen
		tampilMenu();
		printf("Pilih Menu : ");
		scanf("%d",&p); // input pilihan
		switch(p){ // pilihan
			case 1: // jika pilih 1
				buatFile();
				break; //akhir case 1
			case 2: // jika pilih 2
				tambahFile();
				break;
			case 3: // jika pilih 3
				tampilFile();
				break;
			case 4: // jika pilih 4
				hapusFile();
				break;
			case 5: // jika pilih 5
				return 0;//keluar program
				break;
			default: // jika pilih angka selain 1-5
				printf("Menu yang anda masukan tidak Valid");
		}
		getch(); // get character buat berenti sebentar buat pencet enter/tombol lain
	}while(p!=5);//loop akan terus berjalan dengan kondisi p(pilihan menu) bukan 5
}
