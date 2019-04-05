# SoalShift_Modul3_F13
## Kelompok F13
## Arini Puspitasari (05111740000040)
## Nur Muhammad Husnul Habib Yahya (05111740000094)

### Soal 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120

Jawaban :
1. Menghitung nilai faktorial yang diinginkan
```
void* faktorial(void* f)
{
    int* input;
    input = (int*) f; //harus dicasting karena address menyimpan alamat sedangkan alamat untuk semua tipe data panjangnya sama tapi ketika kita butuh value harus tau panjang memori yang digunakan
    int angka= *input;
    int i;
    long long simpan=1;
    for(i=1; i<=angka; i++) //menghitungnya dimulai dari 1, increament
    {
        simpan=simpan*i;
    }
    hasil[angka]=simpan;
    //return NULL;
}
```
2. Membuat thread agar bisa menjalankannya perintah secara parallel (banyak input)
3. Menggunakan join thread agar selesainya bersama (parallel)
4. Sorting nilai faktorial menggunakan bubblesorting dari terkecil ke terbesar
```
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 1; i <= n; i++)
       for (j = i + 1; j <= n; j++){  
           if (arr[i] > arr[j]){
                swap(&arr[j], &arr[i]);
           }
       }
} 
```
5. Munculkan nilai faktorial dengan berurutan
```
for(a=1; a<=panjang; a++)
    {
        printf("%d! = %lld\n", arr[a], hasil[arr[a]]);
    }
```

### Soal 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:

	a. Terdapat 2 server: server penjual dan server pembeli
	b. 1 server hanya bisa terkoneksi dengan 1 client
	c. Server penjual dan server pembeli memiliki stok barang yang selalu sama
	d. Client yang terkoneksi ke server penjual hanya bisa menambah stok
		Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
	e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
		Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
	f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
		Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
		Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
	g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali
	h. Menggunakan thread, socket, shared memory

Jawaban :
1. Buat 2 client (soal2_client dan soal2_pclient) dan 2 server (soal2_server dan soal2_pserver)
2. Kedua server saling berhubungan serta berguna untuk menghitung stok barang yang ada
3. Setiap server berpasangan dengan 1 client (soal2_server dengan soal2_client dan soal2_pserver dengan soal2_pclient), keduanya dipasangkan menggunakan port yang sama
4. Apabila soal2_pclient bekerja dan berhasil melakukan transaksi maka jumlah stok barang di soal2_pserver berkurang begitu juga dengan soal2_server
5. Apabila soal2_client bekerja dan berhasil melakukan transaksi maka jumlah stok barang di soal2_server bertambah begitu juga dengan soal2_pserver
6. Setiap 5 detik sekali server penjual akan mencetak stoknya menggunakan
```
void *Print(void *argv){
    while(1){
        printf("%d\n", *stock);
        sleep(5);
    }
}
```

### Soal 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

	a. Terdapat 2 karakter Agmal dan Iraj
	b. Kedua karakter memiliki status yang unik
		Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
		Iraj memiliki Spirit_Status, di awal program memiliki status 100
		Terdapat 3 Fitur utama
			All Status, yaitu menampilkan status kedua sahabat
			   Ex: Agmal WakeUp_Status = 75 
			     Iraj Spirit_Status = 30
			“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
			“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
		Terdapat Kasus yang unik dimana:
			Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
			Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
		Program akan berhenti jika Salah Satu :
			WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
			Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
		Syarat Menggunakan Lebih dari 1 Thread

Jawaban :
1. Stat awal untuk Agmal 0 sedangkan stat awal untuk Iraj 100
2. Apabila fungsi Agmal dipanggil maka nilai Agmal bertambah 1
```
if(data->panggilAkmal == 1){
            data->countAkmal += 1;
            data->statAkmal += 15;
            data->panggilAkmal = 0;
        }
```
3. Apabila fungsi Iraj dipanggil maka nilai Iraj berkurang 20
```
if(data->panggilSiraj == 1){
            data->countSiraj += 1;
            data->statSiraj -= 20;
            data->panggilSiraj = 0;
        }
```
4. Apabila fungsi Agmal sudah dipanggil sebanyak 3 kali maka fungsi Iraj sleep selama 10 detik
```
if(data->countAkmal == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            data->sleepSiraj = 10;
            data->countAkmal = 0;
	    }
```
5. Apabila fungsi Iraj sudah dipanggil sebanyak 3 kali maka fungsi Agmal sleep selama 10 detik
```
if(data->countSiraj == 3){
            printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
            data->sleepAkmal = 10;
            data->countSiraj = 0;
        }
```
6. Apabila nilai Agmal sudah mencapai 100 ataupun nilai Iraj sudah 0 maka proses akan berhenti dan akan exit

### Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
	
	Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
	Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
	Ketika Mengekstrak file .zip juga harus secara bersama-sama
	Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
	Wajib Menggunakan Multithreading
	Boleh menggunakan system

Jawaban :
1. Buat 2 proses, proses1 berguna untuk file1 sedangkan proses2 untuk file2
2. Simpan list proses di SimpanProses1.txt
```
    status += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses1/SimpanProses1.txt");
```
3. Kompres file tersebut dengan format KompresProses1.zip dan hapus file SimpanProses1.txt
```
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses1/; zip KompresProses1.zip SimpanProses1.txt; rm SimpanProses1.txt");
```
4. Sleep program selama 15 detik dan zip kembali folder yang telah di kompres tadi
```
    status += 7;
    while(status != 20){}
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses1/; unzip KompresProses1.zip");
}
```
5. Simpan list proses di SimpanProses2.txt
```
    status += 1;
    while(status != 2){}
    system("ps -aux | head -n 11 > /home/nmhhabiby/Documents/FolderProses1/SimpanProses2.txt");
```
6. Kompres file tersebut dengan format KompresProses2.zip dan hapus file SimpanProses2.txt
```
    status += 2;
    while(status != 6){}
    system("cd /home/nmhhabiby/Documents/FolderProses2/; zip KompresProses2.zip SimpanProses2.txt; rm SimpanProses2.txt");
```
7. Sleep program selama 15 detik dan zip kembali folder yang telah di kompres tadi
```
    status += 7;
    while(status != 20){}
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    system("cd /home/nmhhabiby/Documents/FolderProses2/; unzip KompresProses2.zip");
}
```
8. Buat thread agar semua proses dilaksanakan secara bersama
```
int main(){
    pthread_t proses1, proses2;
    status = 0;
    pthread_create(&proses1, NULL, Proses1, NULL);
    pthread_create(&proses2, NULL, Proses2, NULL);
    pthread_join(proses1, NULL);
    pthread_join(proses2, NULL);
    printf("\n");
}
```

### Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
	
	a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
	b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
	c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
	d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
	e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
	f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
		Pembeli (terintegrasi dengan game)
			Dapat mengecek stok makanan yang ada di toko.
			Jika stok ada, pembeli dapat membeli makanan.
		Penjual (terpisah)
			Bisa mengecek stok makanan yang ada di toko
			Penjual dapat menambah stok makanan.
	Spesifikasi program:
	A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
	B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
	C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :
		Standby Mode
		Health : [health status]
		Hunger : [hunger status]
		Hygiene : [hygiene status]
		Food left : [your food stock]
		Bath will be ready in [cooldown]s
		Choices
		1. Eat
		2. Bath
		3. Battle
		4. Shop
		5. Exit
	D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :
		Battle Mode
		Monster’s Health : [health status]
		Enemy’s Health : [enemy health status]
		Choices
		1. Attack
		2. Run
	E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :
		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
		1. Buy
		2. Back
	F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :
		Shop
		Food stock : [shop food stock]
		Choices
		1. Restock
		2. Exit
	G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

Jawaban :
1. Buat shared memory
```
    key_t key = 6969;
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0777);
    stock = shmat(shmid, NULL, 0);
    c = 'z';
    stateMenu = 0;
    isExit = 0;
    system("clear");
    pthread_t hunger, regen, input, render, check, hygiene, bath;
    slave = malloc(sizeof(struct budak));
```
2. Status awal untuk monster setelah dibuat
```
    slave->hunger = maxHunger;
    slave->hygiene = maxHigen;
    slave->health = maxHp;
```
3. Buat thread agar semua program dapat berjalan bersama
```
    pthread_create(&hunger, NULL, Hunger, NULL);
    pthread_create(&regen, NULL, Regen, NULL);
    pthread_create(&input, NULL, Input, NULL);
    pthread_create(&render, NULL, Render, NULL);
    pthread_create(&check, NULL, CheckStat, NULL);
    pthread_create(&hygiene, NULL, Hygiene, NULL);
    pthread_create(&bath, NULL, Bath, NULL);
 ```
 4. Terdapat fungsi input yang dijalankan secara terus menerus yang berfungsi untuk menampilkan menu dan memasukkan pilihan dari menu yang ditampilkan
 5. Fungsi Render digunakan untuk menampilkan daftar menu sesuai dengan state menu yang diminta pada fungsi inout
 6. Apabila stateMenu==0 maka akan menampilkan menu standby mode
 ```
 	    if(stateMenu == 0){
            printf("Standby Mode\n");
            printf("Health : %d\nHunger : %d\nHygiene : %d\n", slave->health, slave->hunger, slave->hygiene);
            printf("Food left : %d\nBath will be ready in %ds\n", slave->food, slave->bathCd);
            printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        }
```
7. Apabila stateMenu==1 maka akan menampilkan menu battle mode
 ```
 	    printf("Battle Mode\n");
            printf("Monster's Health : %d\nEnemy's Health : %d\n", slave->health, enemyHP);
            printf("Choice\n1. Attack\n2. Run\n");
        }
```
8. Apabila stateMenu bernilai selain 0 atau 1 maka akan menampilkan menu shop mode
 ```
 	    printf("Shop Mode\n");
            printf("Shop food stock : %d\nYour food stock : %d\n", *stock, slave->food);
            printf("Choice\n1. Buy\n2. Back\n");
	    }
```
9. Buat fungsi untuk Regen untuk mengupdate status health monster
```
void *Regen(){
    while(1){
        sleep(10);
        if(stateMenu != 1){
            slave->health += 5;
        }
    }
}
```
10. Buat fungsi untuk Regen untuk mengupdate status bath monster
```
void *Bath(){
    while(1){
        while(slave->bathCd > 0){
            sleep(1);
            slave->bathCd -= 1;
        }
    }
}
```
11. Buat fungsi untuk Regen untuk mengupdate status hygiene monster
```
void *Hygiene(){
    while(1){
        sleep(30);
        if(stateMenu != 1)
            slave->hygiene -= 10;
    }
}
```
12. Buat fungsi untuk checkstatus
```
if(slave->health <= 0){
            printf("AWWWWW, si %s mati karena kehabisan nyawa\n", slave->name);
            isExit = 1;
        }
        else if(slave->hunger <= 0){
            printf("AWWWWW, si %s mati karena kelaparan\n", slave->name);
            isExit = 1;
        }
        else if(slave->hygiene <= 0){
            printf("AWWWWW, si %s mati karena terlalu jorok\n", slave->name);
            isExit = 1;
        }
```
