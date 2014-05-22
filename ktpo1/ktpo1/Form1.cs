using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace ktpo1
{
    public partial class Form1 : Form
    {
        FileStream fout = new FileStream("file.txt", FileMode.Open);
      
         
        public Form1()
        {
            InitializeComponent();
            

        }
        private void sort(int c,int k,string[] sNums)
        {
            int temp;
            int[] nums = new int[c]; // объявляем новый массив с количеством элементов = c.

            for (int i = 0; i < c; i++)
                nums[i] = int.Parse(sNums[i]);
            for (int i = 1; i <= c; i = i + 2)
            {
                if (nums[i] > 0)
                {
                    nums[i] = nums[i] + k;
                }
            }

            for (int i = 0; i < c / 2; i++)
            {
                temp = nums[i * 2 + 1];
                nums[i * 2 + 1] = nums[i * 2];
                nums[i * 2] = temp;
            }
            for (int i = 0; i < nums.Length; i++)
            {
                textBox3.Text += nums[i].ToString() + "  ";

            }

            FileStream fs = new FileStream("output.txt", FileMode.OpenOrCreate, FileAccess.Write);
            StreamWriter sw = new StreamWriter(fs);
            for (int i = 0; i < c; i++)
            {
                sw.WriteLine(nums[i] + " ");
            }
            sw.Close();
        }
        private void button1_Click(object sender, EventArgs e)
        {
          
            try
            {
                textBox3.Clear();
                int c = int.Parse(textBox1.Text); // Парсим значение из текстового поля textBox1.
                int k = int.Parse(textBox4.Text);
                string[] sNums = textBox2.Text.Split(' '); // Разбиваем текст из текстового поля textBox2, на массив строк, разделителем является пробел.
                if (c > sNums.Length)
                {
                    MessageBox.Show("ERROR 01. Длина массива не соответствует введенному! Дополните массив до нужного размера");
                    return;
                }
                if (c <= 1)
                {
                    MessageBox.Show("ERROR 02. Размер массива должен быть больше 1");
                    textBox2.Clear();
                    return;
                }
                if (c < sNums.Length)
                {
                    MessageBox.Show("ERROR 03. Длина массива не соответствует введенному! Вы ввели большое количество символов");
                    return;
                }
                if (c % 2 != 0)
                {
                    MessageBox.Show("ERROR 04. Введите четное число в поле размерность массива");
                    textBox1.Clear();
                    textBox2.Clear();
                    return;

                }
                if (textBox4.Text == null)
                {
                    MessageBox.Show("ERROR 05. Введите произвольное число К");
                }
                if (textBox1.Text == null)
                {
                    MessageBox.Show("ERROR 06. Введите размерность массива");
                }
               
                sort(c, k,  sNums);
              
            }
            catch (IndexOutOfRangeException)
            {
                MessageBox.Show("ERROR 07. Длина массива не соответствует введенному!");
                textBox2.Clear();
                return;
            }
            catch
            {

                MessageBox.Show("ERROR 08. Проверьте исходные данные.");

           }
            

        }

        //ВВОД ИЗ ФАЙЛА
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                textBox3.Clear();
                int c = int.Parse(textBox1.Text);
                int k = Convert.ToInt32(textBox4.Text);
                textBox2.Text = File.ReadAllText("out.txt");
                string[] sNums = textBox2.Text.Split(' '); // Разбиваем текст из текстового поля textBox2, на массив строк, разделителем является пробел.
                if (c > sNums.Length)
                {
                    MessageBox.Show("ERROR 01. Длина массива не соответствует введенному!");
                    return;
                }
                if (c <= 1)
                {
                    MessageBox.Show("ERROR 02. Размер массива должен быть больше 1");
                    textBox2.Clear();
                    return;
                }
                sort(c, k, sNums);

            }
            catch (IOException ex)
            {
                //MessageBox.Show("Ошибка открытия файла");
                MessageBox.Show("ERROR 09 Ошибка открытия файла ", ex.Message);
            }
            catch
            {
                MessageBox.Show("ERROR 08. Проверьте исходные данные");
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
            textBox4.Clear();
        }

        
    }
}
//динамический массив ограниченный памятью. целочисленных элементов.