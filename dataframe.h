#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include <stdlib.h>
template <typename data_type>


class DataFrame
{
public:
    DataFrame(){
        data = std::vector<std::vector<data_type>>();
    }

    DataFrame(const std::vector<std::vector<data_type>> & Data ){
        data = Data;
    }

    std::vector<int> get_size() const{return {data.size(), data[0].size()};}
    int get_column() const{return data[0].size();}
    int get_row() const{return data.size();}

    void append (std::vector<data_type> vec){
        data.push_back(vec);
    }

    std::vector<data_type> operator [](int index) const{return data[index];}

    void read_csv(std::string path){
        std::ifstream file;
        std::string line, sub_line;
        data_type tmp = 0;
        data_type num = 0;
        std::vector<data_type> tmp_vector;
        file.open(path);
        data = std::vector<std::vector<data_type>>();
        int j = -1;

        while (file.good()){
            getline(file, line, '\n');
            sub_line = "";
            j++;
            data.push_back(tmp_vector);

            for (int i = 0; i < line.length(); i++){
                char symbol = line[i];

                if (symbol != ','){
                    sub_line += symbol;
                }

                else {

                    if(std::is_same<data_type, int>::value){
                        num = atoi(sub_line.c_str());
                    }

                    else if (std::is_same<data_type, double>::value){
                        num = atof(sub_line.c_str());
                    }
                    data[j].push_back(num);
                    sub_line = "";
                }
            }
            if(std::is_same<data_type, int>::value){
                num = atoi(sub_line.c_str());
            }

            else if (std::is_same<data_type, double>::value){
                num = atof(sub_line.c_str());
            }
            data[j].push_back(num);
            sub_line = "";
        }
    }

    std::vector<std::vector<data_type>> get_vector(){
        return data;
    }

    std::vector<data_type> get_vector_column(int index) const{
        std::vector<data_type> column;
        for (int i = 0; i < get_row(); ++i) {
            column.push_back(data[i][index]);
        }
        return column;
    }

    static bool find(std::vector<data_type> vec, data_type item){
        for (auto value: vec) {

            if(value == item){
                return true;
            }
        }
        return false;
    }

    static std::vector<data_type> unique(std::vector<data_type> data){
        std::vector<data_type> data_unique;
        for (int i = 0;i < data.size(); ++i) {

            if (!(find(data_unique, data[i]))){
                data_unique.push_back(data[i]);
            }

        }
        return data_unique;
    }

    //транспонирование матриц
    void T()
    {
        std::vector<std::vector<data_type>> new_matrix;
        std::vector<data_type> tmp;
        int column_size = get_column();
        int row_size = get_row();

        for(int i = 0; i < row_size; i++)
        {

            for(int j = 0; j < column_size; j++)
            {
                if (i == 0)
                {
                    new_matrix.push_back(tmp);
                }
                new_matrix[j].push_back(data[i][j]);
            }
        }

        data = new_matrix;
    }

    DataFrame operator-(data_type number) const
    {
        std::vector<std::vector<data_type>> new_data = data;
        for(int i = 0; i < get_row(); i++)
        {
            for(int j = 0; j < get_column(); j++)
            {
                new_data[i][j] -= number;
            }
        }
        return DataFrame(new_data);
    }

    DataFrame operator*(data_type number) const
    {
        std::vector<std::vector<data_type>> new_data = data;
        for(int i = 0; i < get_row(); i++)
        {
            for(int j = 0; j < get_column(); j++)
            {
                new_data[i][j] *= number;
            }
        }
        return DataFrame(new_data);
    }

    DataFrame operator-(DataFrame other)
    {
        std::vector<std::vector<data_type>> new_data = data;
        if(other.get_size() == get_size())
        {
            for(int i = 0; i < get_row(); i++)
            {
                for(int j = 0; j < get_column(); j++)
                {
                    new_data[i][j] -= other[i][j];
                }
            }
        }
        return DataFrame(new_data);
    }

    //евклидово растояние
    static data_type dist(const std::vector<data_type> & vec1, const std::vector<data_type> &vec2)
    {
        DataFrame matr1 = DataFrame({vec1}), matr2 = DataFrame({vec2});
        matr1 = matr1 - matr2;
        data_type ans = 0;
        for (int i = 0;i < matr1.get_row(); i++)
        {
            for(int j = 0;j < matr1.get_column(); j++)
            {
                ans += pow(matr1[i][j], 2);
            }
        }

        return sqrt(ans);

    }

    //перегрузка операторов: +, -, *, /
    DataFrame operator+(const DataFrame& other) const
    {
        std::vector<std::vector<data_type>> new_data = data;
        if(other.get_size() == get_size())
        {
            for(int i = 0; i < get_row(); i++)
            {
                for(int j = 0; j < get_column(); j++)
                {
                    new_data[i][j] += other[i][j];
                }
            }
        }
        return DataFrame(new_data);
    }

private:
    //вектор данных
    std::vector<std::vector<data_type>> data;
};

#endif // DATAFRAME_H
