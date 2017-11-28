#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

string r_s(size_t length);

int main() {

    vector<string> genres   = {"Comedy", "Drama", "Horror", "Thriller"};
    vector<string> awards   = {"Oscar, Best Director", "Oscar, Best Film", "Oscar, Best Setting",
                               "Oscar, Best Actor", "MTV, Best Director", "MTV, Best Actor"};
    vector<string> names    = {"Adi", "Andrea", "Giulio", "Mauro", "Giovanni"};
    vector<string> surnames = {"Bianchi", "Rossi", "Diaconi", "Blui", "Macri", "Karini", "MottaSanGiuanni"};
    vector<string> chnames1 = {"The", "A", "The Only", "Il", "Maybe"};
    vector<string> chnames2 = {" Magnificent", " Unique", " Useless", " Modern", " Colorful", " Macro"};
    vector<string> chnames3 = {" Flash", " Batman", " Arrow", " DeadPool", " Dolfo", " CatWoman", " Zuckemberg", " Aquaman"};
    
    srand(time(NULL));

    string Omovies = "";
    string Oactors = "";
    string Oawards = "";

    ofstream database("database.sql");

    vector<pair<string,string>> movies;

    int moviesAmount = 200;
    for (int i = 0; i < moviesAmount; ++i) {
        pair<string,string> m = make_pair("Title_" + to_string(rand()%50), to_string(rand()%120 + 1900));
        movies.push_back(m);
        string movS = "('" + m.first + "', " + m.second + ", 'D_" + to_string(rand()%30)
                      + "', 'COU_" + r_s(3) + "', " + to_string(rand()%11)
                      + ", '" + genres[rand()%genres.size()] + "', " + to_string((rand()%15 + 15) * 1000000)
                      + ", 'PRO_" + to_string(rand()%10) + "'),";
        Omovies += movS + "\n";
    }
    Omovies = Omovies.substr(0, Omovies.size()-2) + ";\n\n\n";
    
    int actorsAmount = 200;
    for(int i=0; i<actorsAmount; i++){
        pair<string,string> hisMov = movies[rand()%moviesAmount];
        string act = "('" + hisMov.first + "', " + hisMov.second
                     + ", '" + chnames1[rand()%chnames1.size()] + chnames2[rand()%chnames2.size()] + chnames3[rand()%chnames3.size()]
                     + "', '" + names[rand()%names.size()] + " " + surnames[rand()%surnames.size()] + "'),";
        Oactors += act + "\n";
    }
    Oactors = Oactors.substr(0, Oactors.size()-2) + ";\n\n\n";

    int awardsAmount = 200;
    for(int i=0; i<awardsAmount; i++){
        pair<string,string> hisMov = movies[rand()%moviesAmount];
        string awa = "('" + hisMov.first + "', " + hisMov.second
                     + ", '" + awards[rand()%awards.size()] + "', '"
                     + ((rand()%3==0) ? "WON" : "NOMINATED") + "'),";
        Oawards += awa + "\n";
    }
    Oawards = Oawards.substr(0, Oawards.size()-2) + ";\n\n\n";

    string Pezzo1 =
            "-- --------------------------------------------------------\n"
            "-- Host:                         sci-didattica.unitn.it\n"
            "-- Versione server:              5.7.20-0ubuntu0.16.04.1 - (Ubuntu)\n"
            "-- S.O. server:                  Linux\n"
            "-- HeidiSQL Versione:            9.4.0.5125\n"
            "-- --------------------------------------------------------\n"
            "\n"
            "/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;\n"
            "/*!40101 SET NAMES utf8 */;\n"
            "/*!50503 SET NAMES utf8mb4 */;\n"
            "/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;\n"
            "/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;\n"
            "\n"
            "\n"
            "-- Dump della struttura del database db_219\n"
            "CREATE DATABASE IF NOT EXISTS `db_219` /*!40100 DEFAULT CHARACTER SET latin1 */;\n"
            "USE `db_219`;\n"
            "\n"
            "-- Dump della struttura di tabella db_219.ACTORS\n"
            "CREATE TABLE IF NOT EXISTS `ACTORS` (\n"
            "  `Title` varchar(75) NOT NULL,\n"
            "  `Year` int(11) NOT NULL,\n"
            "  `CharacterName` varchar(75) NOT NULL,\n"
            "  `Name` text NOT NULL,\n"
            "  PRIMARY KEY (`Title`,`Year`,`CharacterName`),\n"
            "  CONSTRAINT `ACTORS_ibfk_1` FOREIGN KEY (`Title`, `Year`) REFERENCES `MOVIES` (`Title`, `Year`) ON DELETE CASCADE ON UPDATE CASCADE\n"
            ") ENGINE=InnoDB DEFAULT CHARSET=latin1;\n"
            "\n"
            "-- Dump dei dati della tabella db_219.ACTORS: ~39 rows (circa)\n"
            "/*!40000 ALTER TABLE `ACTORS` DISABLE KEYS */;\n"
            "INSERT IGNORE INTO `ACTORS` (`Title`, `Year`, `CharacterName`, `Name`) VALUES\n";

    string Pezzo2 =
            "/*!40000 ALTER TABLE `ACTORS` ENABLE KEYS */;\n"
            "\n"
            "-- Dump della struttura di tabella db_219.AWARDS\n"
            "CREATE TABLE IF NOT EXISTS `AWARDS` (\n"
            "  `Title` varchar(75) NOT NULL,\n"
            "  `Year` int(11) NOT NULL,\n"
            "  `Award` varchar(75) NOT NULL,\n"
            "  `Result` enum('WON','NOMINATED') NOT NULL,\n"
            "  PRIMARY KEY (`Title`,`Year`,`Award`),\n"
            "  CONSTRAINT `AWARDS_ibfk_1` FOREIGN KEY (`Title`, `Year`) REFERENCES `MOVIES` (`Title`, `Year`) ON DELETE CASCADE ON UPDATE CASCADE\n"
            ") ENGINE=InnoDB DEFAULT CHARSET=latin1;\n"
            "\n"
            "-- Dump dei dati della tabella db_219.AWARDS: ~63 rows (circa)\n"
            "/*!40000 ALTER TABLE `AWARDS` DISABLE KEYS */;\n"
            "INSERT IGNORE INTO `AWARDS` (`Title`, `Year`, `Award`, `Result`) VALUES\n";

    string Pezzo3 =
            "/*!40000 ALTER TABLE `AWARDS` ENABLE KEYS */;\n"
            "\n"
            "-- Dump della struttura di tabella db_219.MOVIES\n"
            "CREATE TABLE IF NOT EXISTS `MOVIES` (\n"
            "  `Title` varchar(75) NOT NULL,\n"
            "  `Year` int(11) NOT NULL,\n"
            "  `Director` text NOT NULL,\n"
            "  `Country` text NOT NULL,\n"
            "  `Rating` int(11) NOT NULL,\n"
            "  `Genre` text NOT NULL,\n"
            "  `Gross` int(11) NOT NULL,\n"
            "  `Producer` text NOT NULL,\n"
            "  PRIMARY KEY (`Title`,`Year`)\n"
            ") ENGINE=InnoDB DEFAULT CHARSET=latin1;\n"
            "\n"
            "-- Dump dei dati della tabella db_219.MOVIES: ~196 rows (circa)\n"
            "/*!40000 ALTER TABLE `MOVIES` DISABLE KEYS */;\n"
            "INSERT IGNORE INTO `MOVIES` (`Title`, `Year`, `Director`, `Country`, `Rating`, `Genre`, `Gross`, `Producer`) VALUES\n";

    string Pezzo4 =
            "/*!40000 ALTER TABLE `MOVIES` ENABLE KEYS */;\n"
            "\n"
            "/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;\n"
            "/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;\n"
            "/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;\n";

    database << Pezzo1 + Oactors + Pezzo2 + Oawards + Pezzo3 + Omovies + Pezzo4;

    return 0;
}

string r_s(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
                "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    string str(length, 0);
    generate_n(str.begin(), length, randchar);
    return str;
}