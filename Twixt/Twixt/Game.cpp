#include "Game.h"


Game::Game() :
	m_board{},
	m_isRedTurn{ true }
{

}

void Game::Initialize(int size, const std::string& redPlayerName, const std::string& blackPlayerName)
{
	m_redPlayer = Player{ Color::Red, redPlayerName };
	m_blackPlayer = Player{ Color::Black, blackPlayerName };
	m_board.SetSize(size);

}

void Game::SaveGame()
{
	std::ofstream out("save.txt");
	out << m_board.GetSize() << "\n";
	out << m_board;
	std::vector<Link> links = m_board.GetLink();
	out << links.size();
	for (int i = 0; i < links.size(); i++)
		out << links[i] << " ";
	m_board.Reset();
	out << "\n";
	out << m_isRedTurn << "\n";
}

void Game::NewGame()
{
	std::string redPlayerName;
	std::string blackPlayerName;

	std::cout << "Enter the name of the Red Player: ";
	std::cin >> redPlayerName;

	std::cout << "Enter the name of the Black Player: ";
	std::cin >> blackPlayerName;

	m_redPlayer.SetName(redPlayerName);
	m_blackPlayer.SetName(blackPlayerName);

	std::cout << "Enter the size of the board: ";
	int size;
	std::cin >> size;

	m_board.SetSize(size);
	std::cout << m_board;
	std::cout << std::endl;
}

void Game::RestoreGame()
{
	std::ifstream in("save.txt");
	in >> m_board;
	std::cout << "SIZE IS:" << m_board.GetSize();
	std::string string;
	size_t size;
	in >> size;
	std::vector<std::string> links;
	for (int i = 0; i < size; i++)
	{
		in >> string;
		links.push_back(string);
	}
	RestoreLinks(links);
	bool turn;
	in >> turn;
	m_isRedTurn = turn;
}

void Game::RestoreLinks(std::vector<std::string> link_strings)
{
	for (const std::string& link_string : link_strings)
	{
		std::regex pattern("\\{(-?\\d+),(-?\\d+)\\}-\\{(-?\\d+),(-?\\d+)\\}");

		std::smatch matches;
		if (std::regex_search(link_string, matches, pattern)) {

			size_t x1 = std::stoi(matches[1].str());
			size_t y1 = std::stoi(matches[2].str());
			size_t x2 = std::stoi(matches[3].str());
			size_t y2 = std::stoi(matches[4].str());

			Board::Position startCoordinates, endCoordinates;
			startCoordinates = { x1,y1 };
			endCoordinates = { x2,y2 };

			Peg& startPeg = m_board[startCoordinates].value();
			Peg& endPeg = m_board[endCoordinates].value();


			std::shared_ptr<Peg> start = std::make_shared<Peg>(startPeg);
			std::shared_ptr<Peg> end = std::make_shared<Peg>(endPeg);
			Link link{ start, end };
			m_board.AddLink(link);
		}
		else {
			std::cout << "No match found.\n";
		}
	}
}


void Game::SwitchColorMenu(bool& validMove)
{
	std::cout << m_redPlayer.GetName() << ", you've placed the first red peg.\n";
	std::cout << m_blackPlayer.GetName() << ", choose your color:\n";
	std::cout << "3. Continue with black pegs\n";
	std::cout << "4. Switch to red pegs\n";

	int colorChoice;
	std::string aux;
	std::cin >> colorChoice;

	switch (colorChoice)
	{
	case 3:
		while (!validMove)
		{
			if (MovePeg())
			{
				validMove = true;
				currentPlayer().IncrementNumber();
			}
		}
		break;
	case 4:
		aux = m_redPlayer.GetName();
		m_redPlayer.SetName(m_blackPlayer.GetName());
		m_blackPlayer.SetName(aux);
		while (!validMove)
		{
			if (MovePeg())
				validMove = true;
		}
		break;
	default:
		std::cerr << "Invalid choice.\n";
		break;
	}
}

void Game::MainMenu(bool& validMove, bool& castig)
{
	int option;
	std::cout << "Press 1 for adding a Peg \nPress 2 for adding a Link \nPress 111 if you need a hint for place your next peg\nPress 222 if you need a hint for checking position of your next peg\n";
	std::cin >> option;
	switch (option)
	{
	case 1:
		if (MovePeg())
		{
			validMove = true;
			currentPlayer().IncrementNumber();
		}
		break;
	case 2:
		if (MoveLink(castig))
			validMove = true;
		break;
	case 3:
		//m_board.RemovePeg(2, 3, currentPlayer());
		validMove = true;
		break;
	case 111:
		/*RefferalSystemHint1();*/
		break;
	case 222:
		size_t positionFirst, positionSecond;
		std::cout << "Choose positions for your next peg\n";
		std::cin >> positionFirst >> positionSecond;
		/*RefferalSystemHint2(positionFirst, positionSecond);*/
		break;
	default:
		std::cerr << "Invalid option!\n";
		break;
	}
}
void Game::StartGame()
{
	bool IsGameActiv = true;
	int nrPegs = static_cast<int>(m_board.GetSize()) * 2 + 2;
	int Moves = 0;
	bool castig = false;
	while (m_redPlayer.GetNrPegs() <= nrPegs || m_blackPlayer.GetNrPegs() <= nrPegs)
	{
		bool validMove = false;
		if (m_isRedTurn)
			std::cout << "It's red's turn.\n";
		else
			std::cout << "It's black's turn. \n";
		while (!validMove)
		{
			if (Moves == 1)
				SwitchColorMenu(validMove);
			else
			{
				MainMenu(validMove, castig);
			}
		}

		Moves++;

		std::cout << m_board;
		showLinks(currentPlayer());
		if (castig == true)
			break;
		ChangePlayer();
	}

	if (m_redPlayer.GetNrPegs() >= nrPegs && m_blackPlayer.GetNrPegs() >= nrPegs && castig == false) //remiza
	{
		m_board.SetState(Board::State::Draw);
		std::cout << "It's a tie";
	}
}
void Game::StartAdvancedGameMode4()
{
	m_card.addEffects();
	bool IsGameActiv = true;
	int nrPegs = static_cast<int>(m_board.GetSize()) * 2 + 2;
	int option;
	while (m_redPlayer.GetNrPegs() <= nrPegs || m_blackPlayer.GetNrPegs() <= nrPegs)
	{
		bool validMove = false;
		if (m_isRedTurn)
			std::cout << "It's red's turn.\n";
		else
			std::cout << "It's black's turn. \n";
		while (!validMove)
		{
			std::cout << "Press 1 for adding a Peg \nPress 2 for pick a special Card \nPress 3 for play your special Card";
			std::cin >> option;
			switch (option)
			{
			case 1:
				if (MovePeg())
					validMove = true;
				break;
			case 2:
				if (PickCard() != "")
					validMove = true;
				break;
			case 3:
				if (PlayCard())
					validMove = true;
				else
					validMove = false;
				break;
			default:
				std::cerr << "Invalid option!\n";
				break;
			}
		}

		std::cout << m_board;
		showLinks(currentPlayer());
		/*if (WinConditionsBlack() or WinConditionsRed())
		{
			m_board.SetState(Board::State::Win);
			break;
		}*/
		ChangePlayer();
	}

	//if (m_redPlayer.GetNrPegs() == nrPegs && m_blackPlayer.GetNrPegs() == nrPegs && !WinConditionsBlack() && !WinConditionsRed()) //remiza
	//{
	//	m_board.SetState(Board::State::Draw);
	//	std::cout << "It's a tie!\n";
	//}
}
void Game::ChangePlayer()
{
	m_isRedTurn = !m_isRedTurn;
}

bool Game::CheckOwnPegs(const Peg& pStart, const Peg& pEnd)
{
	if (static_cast<int>(pStart.GetColor()) != static_cast<int>(pEnd.GetColor())
		|| (m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 1)
		|| (!m_isRedTurn && static_cast<int>(pEnd.GetColor()) == 0))
	{
		std::cerr << "You can place a link ONLY between your pegs!\n";
		return false;
	}
	return true;
}

bool Game::CheckPositionsPegs(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd)
{
	if (std::abs(xStart - xEnd) != 1 || std::abs(yStart - yEnd) != 2)
	{
		if (std::abs(xStart - xEnd) != 2 || std::abs(yStart - yEnd) != 1)
		{
			std::cerr << "You cannot place a link between those two pegs!\n";
			return false;
		}
	}
	return true;
}

bool Game::CheckIntersectionsLinks(const Peg& pStart, const Peg& pEnd, int xStart, int yStart, int xEnd, int yEnd)
{
	std::vector<Link>listOfLinks = m_board.GetLink();
	for (int i = 0; i < 2; i++)
	{
		for (const auto& link : listOfLinks)
		{
			int distance1, distance2, distance3, distance4;
			distance1 = std::abs(xStart - static_cast<int>(link.GetPegStart()->GetPosition().first)) + std::abs(yStart - static_cast<int>(link.GetPegStart()->GetPosition().second));
			distance2 = std::abs(xStart - static_cast<int>(link.GetPegEnd()->GetPosition().first)) + std::abs(yStart - static_cast<int>(link.GetPegEnd()->GetPosition().second));
			distance3 = std::abs(xEnd - static_cast<int>(link.GetPegStart()->GetPosition().first)) + std::abs(yEnd - static_cast<int>(link.GetPegStart()->GetPosition().second));
			distance4 = std::abs(xEnd - static_cast<int>(link.GetPegEnd()->GetPosition().first)) + std::abs(yEnd - static_cast<int>(link.GetPegEnd()->GetPosition().second));
			if (distance1 + distance2 + distance3 + distance4 <= 8)
			{
				if ((distance2 == distance3 && (distance1 + distance4 == 4 || distance1 + distance4 == 6))
					|| (distance1 == distance4 && distance2 + distance3 == 4))
				{
					std::cerr << "You cannot place a link above another one!\n";
					return false;

				}
			}
		}
		listOfLinks = m_board.GetLink();
	}
	return true;
}

bool Game::LinkValidation(const Peg& pStart, const Peg& pEnd)
{

	int xStart{ static_cast<int>(pStart.GetPosition().first) };
	int yStart{ static_cast<int>(pStart.GetPosition().second) };
	int xEnd{ static_cast<int>(pEnd.GetPosition().first) };
	int yEnd{ static_cast<int>(pEnd.GetPosition().second) };

	return CheckOwnPegs(pStart, pEnd) && CheckPositionsPegs(pStart, pEnd, xStart, yStart, xEnd, yEnd) && CheckIntersectionsLinks(pStart, pEnd, xStart, yStart, xEnd, yEnd);
}

bool Game::CheckCorners(const size_t& row, const size_t& col, const size_t& size)
{
	if ((row == 0 && col == 0) || (row == 0 && col == size - 1) || (row == size - 1 && col == 0) || (row == size - 1 && col == size - 1))
	{
		std::cerr << "The corners of the board are inaccessible!\n";
		return false;
	}
	return true;
}

bool Game::CheckPerimeter(const size_t& row, const size_t& col, const size_t& size)
{
	if (row < 0 || row > size - 1 || col < 0 || col > size - 1) {
		std::cerr << "You have exceeded the perimeter of the board!\n";
		return false;
	}
	return true;
}


bool Game::CheckEnemyZone(const size_t& row, const size_t& col, const size_t& size)
{
	if (m_isRedTurn)
	{
		if (col == 0 || col == size - 1)
		{
			std::cerr << "You are not allowed to put the piece in the enemy zone!\n";
			return false;
		}
	}
	else
	{
		if (row == 0 || row == size - 1)
		{
			std::cerr << "You are not allowed to put the piece in the enemy zone!\n";
			return false;
		}
	}
	return true;
}

bool Game::PegValidation(const size_t& row, const size_t& col)
{
	size_t size = m_board.GetSize();
	return CheckCorners(row, col, size) && CheckPerimeter(row, col, size) && m_board.IsPlaceOccupied(row, col) && CheckEnemyZone(row, col, size);
}

bool Game::MovePeg() {
	Board::Position position = currentPlayer().GetNextActionPeg();
	auto [row, col] = position;

	if (PegValidation(row, col)) {
		Peg p;

		if (m_isRedTurn) {
			p = Peg{ Color::Red, position };
		}
		else {
			p = Peg{ Color::Black, position };
		}

		m_board[position] = p;


		return true;
	}
	return false;
}

bool Game::MoveLink(bool& castig)
{
	Board::Position startCoordinates, endCoordinates;
	std::pair< Board::Position, Board::Position> get = m_board.GetNextActionLink();
	startCoordinates = get.first;
	endCoordinates = get.second;

	if (m_board[startCoordinates].has_value()) {
		const std::optional<Peg>& start = m_board[startCoordinates];
		if (m_board[endCoordinates].has_value()) {
			const std::optional<Peg>& end = m_board[endCoordinates];

			if (start.has_value() && end.has_value()) {
				Peg& startPeg = m_board[startCoordinates].value();
				Peg& endPeg = m_board[endCoordinates].value();


				if (LinkValidation(startPeg, endPeg)) {
					std::shared_ptr<Peg> start = std::make_shared<Peg>(startPeg);
					std::shared_ptr<Peg> end = std::make_shared<Peg>(endPeg);
					Link link{ start, end };
					m_board.AddLink(link);
					startPeg.AddAdjacentPeg(endPeg);
					endPeg.AddAdjacentPeg(startPeg);
					auto state{ BoardChecker::Check(m_board,startPeg) };
					auto state2{ BoardChecker::Check(m_board,endPeg) };
					if (state == BoardChecker::State::Win || state2 == BoardChecker::State::Win)
					{
						std::cout << std::format("We have a winner!\nCongratulations: {}\n",
							currentPlayer().GetName());
						castig = true;
					}
					return true;
				}
			}
		}
		else {
			std::cerr << "You cannot place a link on a nonexistent peg!\n";
			return false;
		}
	}
	else {
		std::cerr << "You cannot place a link on a nonexistent peg!\n";
		return false;
	}
}


Player& Game::currentPlayer()
{
	if (m_isRedTurn)
		return m_redPlayer;
	else
		return m_blackPlayer;
}

void Game::showLinks(const Player& player) {
	std::vector<Link> links = m_board.GetLink();
	std::cout << "The list of links is: ";
	std::cout << std::endl;

	for (size_t i = 0; i < links.size(); ++i) {
		const Link& link = links[i];
		std::cout << "L" << link << "";

		if (i != links.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}


std::string Game::PickCard()
{
	std::vector<std::string> effects = m_card.GetEffects();
	std::string effect = m_card.getRandomEffect(effects);
	currentPlayer().AddCard(effect);
	std::cout << "You add succesfuly in your deck a card\n";
	return effect;
}

bool Game::PlayCard()
{
	if (currentPlayer().GetCards().empty())
	{
		std::cout << "You don't have any cards\n";
		return false;
	}
	std::string functionToPlay = currentPlayer().GetCards().front();
	currentPlayer().EraseCard();
	std::cout << "Hey " << currentPlayer().GetName() << " you chose to play " << functionToPlay << std::endl;
	if (functionToPlay == "Get2Cards")
	{
		PickCard();
		PickCard();
		return true;
	}
	else if (functionToPlay == "Loses2Cards")
	{
		currentPlayer().EraseCard();
		currentPlayer().EraseCard();
		return true;
	}
	else if (functionToPlay == "PlayExtraTurn")
	{
		return false;
	}
	else if (functionToPlay == "Place2Pillars")
	{
		MovePeg();
		MovePeg();
		return true;
	}
	else if (functionToPlay == "Place2Links")
	{
		std::cout << "If you don't have enaugh pillars to plase a link, please press 0 and choose another option\n";
		std::cout << "Or press 1 and continue with this Card\n";
		int digit;
		std::cin >> digit;
		if (digit == 0)
			return false;
		bool castig = false;
		MoveLink(castig);
		MoveLink(castig);
		return true;
	}
	else if (functionToPlay == "Remove1OpponentPillar")
	{
		std::cout << "If your opponent don't have any pegs, please press 0 and choose another option\n";
		std::cout << "Or press 1 and continue with this Card\n";
		int digit;
		std::cin >> digit;
		if (digit == 0)
			return false;
		std::cout << "Which peg do you want to remove?\n";
		size_t destroyedRow, destroyedCol;
		std::cin >> destroyedRow >> destroyedCol;
		m_board.RemovePeg(destroyedRow, destroyedCol);
		return true;
	}
	else if (functionToPlay == "Remove1OpponentLink")
	{
		std::cout << "If your opponent don't have any links, please press 0 and choose another option\n";
		std::cout << "Or press 1 and continue with this Card\n";
		int digit;
		std::cin >> digit;
		if (digit == 0)
			return false;
		std::cout << "Which link do you want to remove?\n";
		size_t destroyedRow1, destroyedCol1, destroyedRow2, destroyedCol2;
		std::cout << "Peg start:\n";
		std::cin >> destroyedRow1 >> destroyedCol1;
		std::cout << "Peg end:\n";
		std::cin >> destroyedRow2 >> destroyedCol2;
		m_board.RemoveLink(destroyedRow1, destroyedCol1, destroyedRow2, destroyedCol2);
		return true;
	}
	else if (functionToPlay == "MoveBulldozer")
	{
		m_board.MoveBuldozer();
		return true;
	}
}

//void Game::RefferalSystemHint1()
//{
//		std::vector<Peg>pegs = m_board.GetPegs();
//		for (int i = 0; i < pegs.size(); i++)
//		{
//			int number = pegs[i].GetAdjacencyPegs().size();
//			if (number == 1 && pegs[i].GetColor() == currentPlayer().GetColor())
//			{
//				std::cout << "Look a hint: " << currentPlayer().GetName()
//					<< " ,you can place your next peg around this peg " << pegs[i].GetPosition().first
//					<< " " << pegs[i].GetPosition().second << "\n";
//			}	
//		}
//}
//
//void Game::RefferalSystemHint2(size_t firstPosition, size_t secondPosition)
//{
//	bool ok = false;
//	std::vector<Peg>pegs;
//	for (int i = 0; i < m_board.GetPegs().size(); i++)
//	{
//		if (m_board.GetPegs()[i].GetColor() == currentPlayer().GetColor())
//			pegs.push_back(m_board.GetPegs()[i]);
//	}
//	std::vector<Peg>resultDfs = pegs[0].DFS();
//	ok = CheckPositionForHint2(firstPosition, secondPosition, resultDfs);
//	for (int i = 0; i < pegs.size() && ok == false; i++)
//	{
//		if (pegs[i].DFS() != resultDfs)
//		{
//			resultDfs = pegs[i].DFS();
//			ok = CheckPositionForHint2(firstPosition, secondPosition, resultDfs);
//		}
//	}
//	
//}
//
//bool Game::CheckPositionForHint2(size_t firstPosition, size_t secondPosition, std::vector<Peg> resultDfs)
//{
//	for (int i = 0; i < resultDfs.size(); i++)
//	{
//		if (std::abs(static_cast<int>(resultDfs[i].GetPosition().first) - static_cast<int>(firstPosition)) == 1 && std::abs(static_cast<int>(resultDfs[i].GetPosition().second) - static_cast<int>(secondPosition)) == 2)
//		{
//			std::cout << "It is not recommanded to place your peg here because it will be blocked by your enamy\n";
//			return true;
//		}
//		else if (std::abs(static_cast<int>(resultDfs[i].GetPosition().first) - static_cast<int>(firstPosition)) == 2 && std::abs(static_cast<int>(resultDfs[i].GetPosition().second) - static_cast<int>(secondPosition)) == 1)
//		{
//			std::cout << "It is not recommanded to place your peg here because it will be blocked by your enamy\n";
//			return true;
//		}
//	}
//	return false;
//}
