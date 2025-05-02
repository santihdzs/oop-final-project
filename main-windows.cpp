#include <iostream>
#include <sstream>
#include <iomanip> //setw()
#include <fstream>
using namespace std;

class Video{
    //Attributes of each movie/serie
    protected:
    string id;         
    string name;       
    string genre;      
    int duration;      
    float rating;        
    string comment;    
    string genre_option; //needed for disp_genre()

    public:
    Video() {} //Empty constructor
    Video(string i, string n, string g, int d, int r, string c) { //Constructor
        id = i; 
        name = n;
        genre = g;
        duration = d;
        rating = r;
        comment = c;
    }
    void design() {  //Inheritance
        cout << left << setw(5) << "ID" 
             << setw(35) << "Name" 
             << setw(10) << "Genre" 
             << setw(10) << "Time" 
             << setw(10) << "Rating" 
             << "Comment" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
    }
    void disp_all() { //Inheritance
        cout << left << setw(5) << id 
             << setw(35) << name 
             << setw(10) << genre 
             << setw(10) << duration 
             << setw(10) << rating 
             << comment << endl;
    }
    void disp_genre(){ //Polymorphism
        cout << "Which genre are you feeling: "<< endl
        << "1. Drama" << endl
        << "2. Action" << endl
        << "3. Mystery" << endl
        << "Choice: " << endl;
        cin >> genre_option;
        while (genre_option != "1" && genre_option != "2" && genre_option !="3"){
            cout << "Invalid option: " << endl;
            cin >> genre_option;
        }
    }

    int stringLength(string str) { // Utility method for search
        int len = 0;
        while (str[len]) len++;
        return len;
    }

    void search(string searchStr) {
        if (stringLength(searchStr) == 0) return;  // empty name / search matches nothing
        
        for (int i = 0; i <= stringLength(name) - stringLength(searchStr); i++) {
            bool match = true;
            for (int j = 0; j < stringLength(searchStr); j++) {
                char currentChar = name[i + j];
                char searchChar = searchStr[j];
                currentChar = tolower(currentChar);
                searchChar = tolower(searchChar);
                
                if (currentChar != searchChar) {
                    match = false;
                    break;
                }
            }
            if (match){
                disp_all();
                return;
            }
        }
        return;
    }
    void reviewVideo(){
        float newRating;
        cin.ignore();
        cout << "Enter your rating for " << name << "(0-5): ";
        cin >> newRating;

        if(newRating < 0 || newRating > 5){
            cout << "Invalid rating";
            return;
        }
        else{
            rating = (rating + newRating) / 2;
        }
        cin.ignore();
        cout << "Enter your comment for " << name << "(0-5): ";
        getline(cin, comment);
    }

    void saveChanges(ofstream &f){
        f << id << "," << name << "," << genre << "," << duration << "," << rating << "," << comment << endl;
    }
};
class Movies : public Video{
    public:
    Movies() {} //Empty constructor
    Movies(string i, string n, string g, int d, int r, string c) { //Costructor, inherited attributes
        id = i;
        name = n;
        genre = g;
        duration = d;
        rating = r;
        comment = c;
    }
    void disp_genre(Movies m[]){ //Polymorphism
        if (genre_option == "1"){
            cout << "Movies of genre Drama:" << endl;
            for (int i = 0; i < 30; i++){
                if (m[i].genre == "Drama"){
                    m[i].disp_all();
                }
            }
        }
        else if (genre_option == "2"){
            cout << "Movies of genre Action:" << endl;
            for (int i = 0; i < 30; i++){
                if (m[i].genre == "Action"){
                    m[i].disp_all();
                }
            }
        }
        else{
            cout << "Movies of genre Mystery:" << endl;
            for (int i = 0; i < 30; i++){
                if (m[i].genre == "Mystery"){
                    m[i].disp_all();
                }
            }
        }
    }
};
class Series : public Video{
    public:
    Series() {}  //Empty Constructor
    Series(string i, string n, string g, int d, int r, string c) { //Costructor, inherited attributes
        id = i;
        name = n;
        genre = g;
        duration = d;
        rating = r;
        comment = c;
    }
    void disp_genre(Series s[]){ //Polymorphism
        cout << "Series of genre: " << genre_option << endl;
        if (genre_option == "1"){
            cout << "Movies of genre Drama:" << endl;
            for (int i = 0; i < 30; i++){
                if (s[i].genre == "Drama"){
                    s[i].disp_all();
                }
            }
        }
        else if (genre_option == "2"){
            cout << "Movies of genre Action:" << endl;
            for (int i = 0; i < 30; i++){
                if (s[i].genre == "Action"){
                    s[i].disp_all();
                }
            }
        }
        else{
            cout << "Movies of genre Mystery:" << endl;
            for (int i = 0; i < 30; i++){
                if (s[i].genre == "Mystery"){
                    s[i].disp_all();
                }
            }
        }
    }
};
int main(){
    Movies m[30]; 
    Series s[29];
    string line;
    string value[6];
    int j = 0;
    int k = 0;
    int i;
  
    //Open movies file for future use
    ifstream fm("C:\\Users\\Sofia\\Documents\\Programacion\\C\\VS code\\Semestre 2\\tecflix\\data\\movies.csv");
        while (getline(fm,line)){
            stringstream ss(line);
            i = 0;
            while(getline(ss, value[i], ',')){
                i++;
            }
            m[j] = Movies(value[0], value[1], value[2], stoi(value[3]), stoi(value[4]), value[5]);
            j++;
        }
    fm.close(); 
    
    ifstream fs("C:\\Users\\Sofia\\Documents\\Programacion\\C\\VS code\\Semestre 2\\tecflix\\data\\series.csv");
        while (getline(fs,line)){
            stringstream ss(line);
            i = 0;
            while(getline(ss, value[i], ',')){
                i++;
            }
            s[k] = Series(value[0], value[1], value[2], stoi(value[3]), stoi(value[4]), value[5]);
            k++;
        }
    fs.close();
    //TecFlix Menu
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Welcome to TecFlix!!!" << endl;
    while (true){  //Loop until 12 (exit)
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Choose an option from the following menu: " << endl;
    cout << "1. Display all videos" << endl //Done
    << "2. Display all movies" << endl  //Done
    << "3. Display movies by genre" << endl //Done
    << "4. Search movies by name" << endl  //SANTI 
    << "5. Evaluate movie between 0-5" << endl //SANTI
    << "6. Save the changes in the movies file" << endl //SANTI
    << "7. Display all series" << endl  //Done
    << "8. Display series by genre" << endl //Done
    << "9. Search series by name" << endl //SANTI
    << "10. Evaluate series between 0-5" << endl //SANTI
    << "11, Save the changes in the series file" << endl //SANTI
    << "12. Exit" << endl //Done
    << "---------------------------------------------------------------------------------" << endl
    << "Choice: ";
    string option;
    cin >> option;
    while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6"
        && option != "7" && option != "8" && option != "9" && option != "10" && option != "11" && option != "12"){
            cout << "Invalid option, please try again: ";
            cin >> option;
    }
    
    if (option == "1"){ //Display all videos
        m[0].design();
        for (int i = 0; i<30; i++){
            m[i].disp_all();
        }
        for (int i = 0; i<29; i++){
            s[i].disp_all();
        }   
    }
    else if (option == "2"){ //Display all movies
        m[0].design();
        for (int i = 0; i<30; i++){
            m[i].disp_all();
        } 
    }
    else if (option == "3"){ //Display movies by genre 
        Video *ptr = m; //Polymorphism
        ptr -> disp_genre();
        m[0].design();
        m[0].disp_genre(m);
    }
    else if (option == "4"){ //Search movies by name
        string searchTerm;
        cout << "What movie are you looking for?: " << endl;
        cin.ignore();
        getline(cin, searchTerm);
        for (int i = 0; i < 30; i++){
            m[i].search(searchTerm);
        }
    }
    else if (option == "5"){ //Evaluate movie between 0-5
        m[0].design();
        for (int i = 0; i<30; i++){
            m[i].disp_all();
        }

        int revIndex;
        cin.ignore();
        cout << "Select the row number for the movie you want to review: ";
        cin >> revIndex;

        if (revIndex < 0 || revIndex >= 30){
            cout << "Invalid row number, please try again" << endl;
            continue;
        }
        else{
            cout << "Movie found, review the following film? (y/n): ";
            revIndex --;
            m[revIndex].disp_all();
            cin.ignore();
            char verifyRev;
            cin >> verifyRev;
            switch (tolower(verifyRev)) { 
                case 'y':
                    m[revIndex].reviewVideo();
                default:
                    break;
            }
        }
    }
    else if (option == "6"){ //Save changes
        ofstream of("C:\\Users\\Sofia\\Documents\\Programacion\\C\\VS code\\Semestre 2\\tecflix\\data\\movies.csv");
        for (int i = 0; i<30; i++){
            m[i].saveChanges(of);
        }
        of.close();
    }    
    else if (option == "7"){ //Display all series
        s[0].design();
        for (int i = 0; i<29; i++){
            s[i].disp_all();
        } 
    }
    else if (option == "8"){ //Display series by genre
        Video *ptr = s; //Polymorphism
        ptr -> disp_genre();
        s[0].design();
        s[0].disp_genre(s);
    }
    else if (option == "9"){
        string searchTerm;
        cout << "What show are you looking for?: " << endl;
        cin.ignore();
        getline(cin, searchTerm);
        for (int i = 0; i < 29; i++){
            s[i].search(searchTerm);
        }
    }
    else if (option == "10"){
        s[0].design();
        for (int i = 0; i<29; i++){
            s[i].disp_all();
        }

        int revIndex;
        cin.ignore();
        cout << "Select the row number for the episode you want to review: ";
        cin >> revIndex;

        if (revIndex < 0 || revIndex >= 29){
            cout << "Invalid row number, please try again" << endl;
            continue;
        }
        else{
            cout << "Episode found, review the following episode? (y/n): ";
            revIndex --;
            s[revIndex].disp_all();
            cin.ignore();
            char verifyRev;
            cin >> verifyRev;
            switch (tolower(verifyRev)) { 
                case 'y':
                    s[revIndex].reviewVideo();
                default:
                    break;
            }
        }
    }
    else if (option == "11"){
        ofstream of("C:\\Users\\Sofia\\Documents\\Programacion\\C\\VS code\\Semestre 2\\tecflix\\data\\series.csv");
        for (int i = 0; i<29; i++){
            s[i].saveChanges(of);
        }
        of.close();
    }
    else{ //Exit
        exit(0);
    }
    } //Cierre del loop del menú
    return 0;
}