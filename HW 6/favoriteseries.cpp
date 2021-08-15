#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string s1, string s2) {
	userName = s1;
	userSurname = s2;
	vector<series> favSeries;
}

string FavoriteSeries::getFullName() const
{
	return string(userName + " " + userSurname);
}

void FavoriteSeries::addSeries(const series& s) {
	favSeries.push_back(s);
}

bool FavoriteSeries::ifExists(int seriesCode) {
	for (int i = 0; i < favSeries.size(); i++) {
		if (seriesCode == favSeries[i].seriesCode) {
			return true;
		}	
	}
	return false;
}

bool FavoriteSeries::isListEmpty() const {
	if (favSeries.size() < 1) {
		return true;
	}
	return false;
}

void FavoriteSeries::dropSeriesSorted(int code) {
	for (int i = 0; i < favSeries.size(); i++) {
		if (favSeries[i].seriesCode == code) {
			favSeries.erase(favSeries.begin() + i);
		}

	}
}

void FavoriteSeries::displayFavoriteList() const {
	string name;
	vector<episode> allFavEpisodes;
	for (int i = 0; i < favSeries.size(); i++) {
		for (int ii = 0; ii < favSeries[i].episodes.size(); ii++) {
			allFavEpisodes.push_back(favSeries[i].episodes[ii]);
		}
	}
	classSort(allFavEpisodes);

	cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for (int i = 0; i < allFavEpisodes.size(); i++) {
		for (int ii = 0; ii < favSeries.size(); ii++)
		{
			if (allFavEpisodes[i].seriesCode == favSeries[ii].seriesCode) {
				name = favSeries[ii].seriesName;
			}
		}
		cout << allFavEpisodes[i].seriesCode << "," << name << "," << allFavEpisodes[i].episodeName << "," << allFavEpisodes[i].date << "," << allFavEpisodes[i].slot << endl;
	}
}

void FavoriteSeries::displayFavoriteActors() const {
	vector<actors> allFavActors;
	bool doActorExist = false;
	int index = 0;
	for (int i = 0; i < favSeries.size(); i++) {
		for (int ii = 0; ii < favSeries[i].actorNames.size(); ii++) {
			doActorExist = false;
			for (int j = 0; j < allFavActors.size(); j++) {
				if (allFavActors[j].name == favSeries[i].actorNames[ii]) {
					doActorExist = true;
					index = j;
				}
			}
			if (doActorExist) {
				allFavActors[index].score += 1;
			}
			else {
				actors input;
				input.name = favSeries[i].actorNames[ii];
				input.score = 1;
				allFavActors.push_back(input);
			}
		}

	}
	actorSort(allFavActors);
	for (int i = 0; i < allFavActors.size(); i++) {
		cout << allFavActors[i].name << ": " << allFavActors[i].score << endl;
	}
}


bool FavoriteSeries::isConflict(const series& s) const
{
	for (int i = 0; i < favSeries.size(); i++) {
		for (int ii = 0; ii < favSeries[i].episodes.size(); ii++) {
			for (int j = 0; j < s.episodes.size(); j++) {
				if (favSeries[i].episodes[ii].date == s.episodes[j].date && favSeries[i].episodes[ii].slot == s.episodes[j].slot) {
					return true;
				}
			}

			
		}
	}
	return false;
}

void FavoriteSeries::classSort(vector<episode> & v) const {
	int k, j, maxIndex;
	episode temp;
	for (k = 0; k < v.size() - 1; k++) {
		maxIndex = k;
		for (j = k + 1; j < v.size(); j++) {
			if (v[j].date < v[maxIndex].date) {
				maxIndex = j;
			}
			else if (v[j].date == v[maxIndex].date) {

				if (v[j].slot == v[maxIndex].slot) {
					if (v[j].seriesCode < v[maxIndex].seriesCode) {
						maxIndex = j;
					}
				}
				else if (v[j].slot == "MORNING") {
					maxIndex = j;
				}
				else if (v[j].slot == "AFTERNOON" && v[maxIndex].slot != "MORNING") {
					maxIndex = j;
				}
				else if (v[j].slot == "EVENING" && v[maxIndex].slot == "NIGHT") {
					maxIndex = j;
				}
			}
		}
		temp = v[k];
		v[k] = v[maxIndex];
		v[maxIndex] = temp;
	}
}

void FavoriteSeries::actorSort(vector<actors> & v) const {
	int k, j, maxIndex;
	actors temp;
	for (k = 0; k < v.size() - 1; k++) {
		maxIndex = k;
		for (j = k + 1; j < v.size(); j++) {
			if (v[j].score > v[maxIndex].score) {
				maxIndex = j;
			}
			else if (v[j].score == v[maxIndex].score) {
				if (v[j].name < v[maxIndex].name) {
					maxIndex = j;
				}
			}
		}
		temp = v[k];
		v[k] = v[maxIndex];
		v[maxIndex] = temp;
	}
}




