#pragma GCC optimize("Ofast")

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <complex>

namespace bode {

	using namespace std;

	template<typename _Tp>
		using Ptr = shared_ptr<_Tp>;
	
	template<typename _Tp, typename... _Args>
    inline shared_ptr<_Tp>
    New(_Args&&... __args)
    {
      typedef typename std::remove_const<_Tp>::type _Tp_nc;
      return std::allocate_shared<_Tp>(std::allocator<_Tp_nc>(),
				       std::forward<_Args>(__args)...);
    }

	enum class SyntaxKind
	{
		// Tokens
		BadToken,
		EndOfFileToken,
		WhitespaceToken,
		VariableToken,
		ImmVariableToken,
		PlusToken,
		MinusToken,
		StarToken,
		SlashToken,
		OpenParenthesisToken,
		CloseParenthesisToken,
		LiteralToken,

		// Expressions
		BinaryExpression,
		UnaryExpression,
		NumberExpression,
		VariableExpression,
		ImmVariableExpression,
		ParenthesizedExpression,
		// MonomialExpression,
		// PolynomialExpression,
	};

	const char* ToString(SyntaxKind kind)
	{
		switch (kind)
		{
		 case SyntaxKind::BadToken:
			return "BadToken";
		 case SyntaxKind::EndOfFileToken:
			return "EndOfFileToken";
		 case SyntaxKind::WhitespaceToken:
			return "WhitespaceToken";
		 case SyntaxKind::VariableToken:
			return "VariableToken";
		 case SyntaxKind::ImmVariableToken:
			return "ImmVariableToken";
		 case SyntaxKind::PlusToken:
			return "PlusToken";
		 case SyntaxKind::MinusToken:
			return "MinusToken";
		 case SyntaxKind::StarToken:
			return "StarToken";
		 case SyntaxKind::SlashToken:
			return "SlashToken";
		 case SyntaxKind::OpenParenthesisToken:
			return "OpenParenthesisToken";
		 case SyntaxKind::CloseParenthesisToken:
			return "CloseParenthesisToken";
		 case SyntaxKind::LiteralToken:
			return "LiteralToken";
		 case SyntaxKind::BinaryExpression:
			return "BinaryExpression";
		 case SyntaxKind::UnaryExpression:
			return "UnaryExpression";
		 case SyntaxKind::NumberExpression:
			return "NumberExpression";
		 case SyntaxKind::VariableExpression:
			return "VariableExpression";
		 case SyntaxKind::ImmVariableExpression:
			return "ImmVariableExpression";
		 case SyntaxKind::ParenthesizedExpression:
			return "ParenthesizedExpression";
		 /*
		 case SyntaxKind::MonomialExpression:
			return "MonomialExpression";
		 case SyntaxKind::PolynomialExpression:
			return "PolynomialExpression";
		 */
		 default:
			return "<__UnexpectedNode__>";
		}
	}

	class SyntaxNode
	{
	 public:
		SyntaxKind Kind;

	 public:
		SyntaxNode()
		{
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			return New<vector<Ptr<SyntaxNode>>>();
		};
	};

	class ExpressionSyntax : public SyntaxNode
	{
	};

	class SyntaxToken : public SyntaxNode
	{
	 public:
		int Position;
		string Text;
		double Value;

	 public:

		SyntaxToken(SyntaxKind kind, const int& position, const string& text)
			: Position(position), Text(text), Value(atoi(text.c_str()))
		{
			Kind = kind;
		}
		~SyntaxToken()
		{
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			return New<vector<Ptr<SyntaxNode>>>();
		}
		
	};

	class NumberExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> NumberToken;

	 public:
		NumberExpressionSyntax(Ptr<SyntaxToken> numberToken)
		{
			NumberToken = numberToken;
			Kind = SyntaxKind::NumberExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(1);
			_this[0] = NumberToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	class VariableExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> VariableToken;

	 public:
		VariableExpressionSyntax(Ptr<SyntaxToken> variableToken)
		{
			VariableToken = variableToken;
			Kind = SyntaxKind::VariableExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(1);
			_this[0] = VariableToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	class ImmVariableExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> ImmaginaryToken;
		double Factor;

	 public:
		ImmVariableExpressionSyntax(Ptr<SyntaxToken> immaginaryToken)
		{
			ImmaginaryToken = immaginaryToken;
			Factor = 1.0;
			Kind = SyntaxKind::ImmVariableExpression;
		}

		ImmVariableExpressionSyntax(Ptr<SyntaxToken> immaginaryToken, double factor)
		{
			ImmaginaryToken = immaginaryToken;
			Factor = factor;
			Kind = SyntaxKind::ImmVariableExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(1);
			_this[0] = ImmaginaryToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	/*
	class MonomialExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> VariableToken;
		int Exponent = 1;

	 public:
		MonomialExpressionSyntax(Ptr<SyntaxToken> variableToken)
		{
			VariableToken = variableToken;
			Kind = SyntaxKind::MonomialExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(1);
			_this[0] = VariableToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	class PolynomialExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> VariableToken;
		Ptr<SyntaxToken> OperatorToken;
		Ptr<NumberExpressionSyntax> NumberExpression;

		int Exponent;

	 public:
		PolynomialExpressionSyntax(Ptr<SyntaxToken> variableToken,Ptr<SyntaxToken> operatorToken, Ptr<NumberExpressionSyntax> numberExpression)
		{
			VariableToken = variableToken;
			Exponent = 1;
			Kind = SyntaxKind::PolynomialExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(1);
			_this[0] = VariableToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};
	*/

	class BinaryExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxNode> Right;
		Ptr<SyntaxToken> OperatorToken;
		Ptr<SyntaxNode> Left;

	 public:
		BinaryExpressionSyntax(Ptr<SyntaxNode> right, Ptr<SyntaxToken> operatorToken, Ptr<SyntaxNode> left)
		{
			Right = right; 
			OperatorToken = operatorToken; 
			Left = left;
			Kind = SyntaxKind::BinaryExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(3);
			_this[0] = Right;
			_this[1] = OperatorToken;
			_this[2] = Left;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	class ParenthesizedExpressionSyntax : public ExpressionSyntax
	{
	 public:
		Ptr<SyntaxToken> OpenParenthesisToken;
		Ptr<SyntaxNode> Expression;
		Ptr<SyntaxToken> CloseParenthesisToken;

	 public:
		ParenthesizedExpressionSyntax(Ptr<SyntaxToken> openParenthesisToken, Ptr<SyntaxNode> expression, Ptr<SyntaxToken> closeParenthesisToken)
		{
			OpenParenthesisToken = openParenthesisToken; 
			Expression = expression; 
			CloseParenthesisToken = closeParenthesisToken;
			Kind = SyntaxKind::ParenthesizedExpression;
		}

		virtual Ptr<vector<Ptr<SyntaxNode>>> GetChildren()
		{
			vector<Ptr<SyntaxNode>> _this(3);
			_this[0] = OpenParenthesisToken;
			_this[1] = Expression;
			_this[2] = CloseParenthesisToken;
			return New<vector<Ptr<SyntaxNode>>>(_this);
		}

	};

	class SyntaxTree
	{
	 public:
		Ptr<SyntaxNode> Root;
		Ptr<SyntaxToken> EndOfFileToken;

	 public:
	  SyntaxTree(Ptr<SyntaxNode> root, Ptr<SyntaxToken> endOfFileToken)
		{
			Root = root;
			EndOfFileToken = endOfFileToken;
		}
		~SyntaxTree()
		{
		}
	};

	class ErrorReporter
	{
	 public:
		Ptr<vector<string>> Diagnistics;

	 private:
		void Report(const string& message)
		{
			Diagnistics->push_back(message);
		}

	 public:
		ErrorReporter()
		{
			Diagnistics = New<vector<string>>();
		}
		~ErrorReporter()
		{
		}

		void ReportBadCharacter(const char& c, const int& position)
		{
			stringstream ss;
			ss 
				<< "Unexpected character <" 
				<< c << "> "
				<< "at position <" << position << ">.";
			
			Report(ss.str());
		}

		void ReportUnexpectedToken(SyntaxKind current, SyntaxKind expected, const int& position)
		{
			stringstream ss;
			ss 
				<< "Unexpected token <" 
				<< ToString(current) << ">, "
				<< "expected <"
				<< ToString(expected) << "> "
				<< "at position <" << position << ">.";
			
			Report(ss.str());
		}

	};

	class Lexer
	{
		Ptr<ErrorReporter> _reporter;

		string _text;
		int _position;

	 public:

		Lexer(string text, Ptr<ErrorReporter> reporter)
			:_text(text), _reporter(reporter)
		{
			_reporter = reporter;
			_position = 0;
		}

		Ptr<SyntaxToken> NextToken()
		{
			if (_position >= _text.size()) 
				return New<SyntaxToken>(SyntaxKind::EndOfFileToken, _position, "\0");

			int start = _position;
			// Whitespace
			if (IsWhitespace(current()))
			{
				while (IsWhitespace(current()))
					_position++;
				return New<SyntaxToken>(SyntaxKind::WhitespaceToken, start, _text.substr(start, _position - start));			
			}

			// Numbers
			if (IsDigit(current()))
			{
				while (IsDigit(current()))
					_position++;
				return New<SyntaxToken>(SyntaxKind::LiteralToken, start, _text.substr(start, _position - start));			
			}

			switch (current())
			{
			 case 's':
				_position++;
				return New<SyntaxToken>(SyntaxKind::VariableToken, start, "s");
			 case 'j':
				_position++;
				return New<SyntaxToken>(SyntaxKind::ImmVariableToken, start, "j");
			 case '+':
				_position++;
				return New<SyntaxToken>(SyntaxKind::PlusToken, start, "+");
			 case '-':
				_position++;
				return New<SyntaxToken>(SyntaxKind::MinusToken, start, "-");
			 case '*':
				_position++;
				return New<SyntaxToken>(SyntaxKind::StarToken, start, "*");
			 case '/':
				_position++;
				return New<SyntaxToken>(SyntaxKind::SlashToken, start, "/");
			 case '(':
				_position++;
				return New<SyntaxToken>(SyntaxKind::OpenParenthesisToken, start, "(");
			 case ')':
				_position++;
				return New<SyntaxToken>(SyntaxKind::CloseParenthesisToken, start, ")");
			}

			_reporter->ReportBadCharacter(_text[_position], _position);
			_position++;
			return New<SyntaxToken>(SyntaxKind::BadToken, start, string(1, _text[start]));
		}

	 private:

		const char& current()
		{
			return _text[_position];
		}

		// Char methods
		static bool IsWhitespace(const char& __c)
		{
			return __c == ' ' || __c == '\t' || __c == '\r' || __c == '\n';
		}
		static bool IsDigit(const char& __c)
		{
			return __c >= '0' && __c <= '9';
		}
	
	};

	class Parser
	{
	 public:
		Ptr<ErrorReporter> _reporter;

	 private:	
		vector<Ptr<SyntaxToken>> _tokens;
		int _position;

	 private:
		Ptr<SyntaxToken> Peek(const int& offset)
		{
			const int& index = _position + offset;
			if (index >= _tokens.size())
				return _tokens[_tokens.size() - 1];
			return _tokens[index];
		}

		Ptr<SyntaxToken> Current()
		{
			return Peek(0);
		}

		Ptr<SyntaxToken> NextToken()
		{
			Ptr<SyntaxToken> next = Current();
			_position++;
			return next;
		}

		Ptr<SyntaxToken> MatchToken(SyntaxKind kind)
		{
			const auto& current = Current();

			if (current->Kind == kind)
				return NextToken();
			
			const auto& position = current->Position;
			_reporter->ReportUnexpectedToken(current->Kind, kind, current->Position);
			
			return New<SyntaxToken>(kind, position, "");
		}

		int GetBinaryPrecedence(SyntaxKind kind)
		{
			switch (kind)
			{
			 case SyntaxKind::StarToken:
			 case SyntaxKind::SlashToken:
				return 2;
			 case SyntaxKind::PlusToken:
			 case SyntaxKind::MinusToken:
				return 1;
			 default:
				return 0;
			}
		}

	 public:
		Parser(string text)
		{
			_reporter = New<ErrorReporter>();
			_position = 0;

			Lexer lexer(text, _reporter);

			auto token = lexer.NextToken();
			while (token->Kind != SyntaxKind::EndOfFileToken)
			{
				if (token->Kind != SyntaxKind::BadToken && 
						token->Kind != SyntaxKind::WhitespaceToken)
					_tokens.push_back(token);
				token = lexer.NextToken();
			}
			_tokens.push_back(token);
		}

		~Parser()
		{
		}

		Ptr<SyntaxTree> Parse()
		{
			auto root = ParseExpression();
			auto endOfFileToken = MatchToken(SyntaxKind::EndOfFileToken);
			return New<SyntaxTree>(root, endOfFileToken);
		}
	
	 private:
		Ptr<SyntaxNode> ParseExpression(int parentPrecedence = 0)
		{
			auto left = ParsePrimaryExpression();

			while (true)
			{
				int precedence = GetBinaryPrecedence(Current()->Kind);
				if(precedence == 0 || precedence <= parentPrecedence) 
					break;

				auto operatorToken = NextToken();
				auto right = ParseExpression(precedence);

				/**/
				if (operatorToken->Kind == SyntaxKind::StarToken &&
						left->Kind == SyntaxKind::NumberExpression &&
						right->Kind == SyntaxKind::ImmVariableExpression)
				{
					Ptr<NumberExpressionSyntax> num = dynamic_pointer_cast<NumberExpressionSyntax>(left);
					Ptr<ImmVariableExpressionSyntax> imm = dynamic_pointer_cast<ImmVariableExpressionSyntax>(right);

					left = New<ImmVariableExpressionSyntax>(imm->ImmaginaryToken, imm->Factor * num->NumberToken->Value);
				}

				else if (operatorToken->Kind == SyntaxKind::StarToken &&
						left->Kind == SyntaxKind::ImmVariableExpression &&
						right->Kind == SyntaxKind::NumberExpression)
				{
					Ptr<NumberExpressionSyntax> num = dynamic_pointer_cast<NumberExpressionSyntax>(right);
					Ptr<ImmVariableExpressionSyntax> imm = dynamic_pointer_cast<ImmVariableExpressionSyntax>(left);

					left = New<ImmVariableExpressionSyntax>(imm->ImmaginaryToken, imm->Factor * num->NumberToken->Value);
				}

				else if (operatorToken->Kind == SyntaxKind::SlashToken &&
						left->Kind == SyntaxKind::ImmVariableExpression &&
						right->Kind == SyntaxKind::NumberExpression)
				{
					Ptr<NumberExpressionSyntax> num = dynamic_pointer_cast<NumberExpressionSyntax>(right);
					Ptr<ImmVariableExpressionSyntax> imm = dynamic_pointer_cast<ImmVariableExpressionSyntax>(left);

					left = New<ImmVariableExpressionSyntax>(imm->ImmaginaryToken, imm->Factor / num->NumberToken->Value);
				}

				else if (operatorToken->Kind == SyntaxKind::StarToken &&
						left->Kind == SyntaxKind::ImmVariableExpression &&
						right->Kind == SyntaxKind::ImmVariableExpression)
				{
					Ptr<ImmVariableExpressionSyntax> immL = dynamic_pointer_cast<ImmVariableExpressionSyntax>(left);
					Ptr<ImmVariableExpressionSyntax> immR = dynamic_pointer_cast<ImmVariableExpressionSyntax>(right);

					auto _left = New<SyntaxToken>(SyntaxKind::LiteralToken, operatorToken->Position, "___");
					_left->Value = immL->Factor * immR->Factor;
					left = New<NumberExpressionSyntax>(_left);
				}

				else if (operatorToken->Kind == SyntaxKind::SlashToken &&
						left->Kind == SyntaxKind::ImmVariableExpression &&
						right->Kind == SyntaxKind::ImmVariableExpression)
				{
					Ptr<ImmVariableExpressionSyntax> immL = dynamic_pointer_cast<ImmVariableExpressionSyntax>(left);
					Ptr<ImmVariableExpressionSyntax> immR = dynamic_pointer_cast<ImmVariableExpressionSyntax>(right);

					auto _left = New<SyntaxToken>(SyntaxKind::LiteralToken, operatorToken->Position, "___");
					_left->Value = immL->Factor / immR->Factor;
					left = New<NumberExpressionSyntax>(_left);
				}
				
				else
				{
					left = New<BinaryExpressionSyntax>(left, operatorToken, right);
				}
			}

			return left;

		}
		
		Ptr<SyntaxNode> ParseParenthesisedExpression() {
			auto openParenthesis = MatchToken(SyntaxKind::OpenParenthesisToken);
			auto expression = ParseExpression();
			auto closeParenthesis = MatchToken(SyntaxKind::CloseParenthesisToken);
			return New<ParenthesizedExpressionSyntax>(openParenthesis, expression, closeParenthesis);
		}

		Ptr<SyntaxNode> ParsePrimaryExpression()
		{
			const auto& current = Current();
			switch (current->Kind)
			{
			 case SyntaxKind::OpenParenthesisToken:
				return ParseParenthesisedExpression();
			 case SyntaxKind::VariableToken:
				return New<VariableExpressionSyntax>(MatchToken(SyntaxKind::VariableToken));
			 case SyntaxKind::ImmVariableToken:
				return New<ImmVariableExpressionSyntax>(MatchToken(SyntaxKind::ImmVariableToken));
			 default:
				return New<NumberExpressionSyntax>(MatchToken(SyntaxKind::LiteralToken));
			}
		}
		
	};

	class Evaluator
	{
	 public:
		Evaluator()
		{
		}
		~Evaluator()
		{
		}

		complex<double> Evaluate(Ptr<SyntaxNode> node, const int& s)
		{
			if (node->Kind == SyntaxKind::NumberExpression)
			{
				Ptr<NumberExpressionSyntax> n = dynamic_pointer_cast<NumberExpressionSyntax>(node);
				return complex<double>(n->NumberToken->Value, 0.0);
			}
			else if (node->Kind == SyntaxKind::VariableExpression)
			{
				return complex<double>((double)s, 1.0);
			}
			else if (node->Kind == SyntaxKind::ImmVariableExpression)
			{
				Ptr<ImmVariableExpressionSyntax> i = dynamic_pointer_cast<ImmVariableExpressionSyntax>(node);
				return complex<double>(0.0, i->Factor);
			}
			else if (node->Kind == SyntaxKind::ParenthesizedExpression)
			{
				Ptr<ParenthesizedExpressionSyntax> p = dynamic_pointer_cast<ParenthesizedExpressionSyntax>(node);
				return Evaluate(p->Expression, s);
			}
			else if (node->Kind == SyntaxKind::BinaryExpression)
			{
				Ptr<BinaryExpressionSyntax> b = dynamic_pointer_cast<BinaryExpressionSyntax>(node);
				switch (b->OperatorToken->Kind)
				{
				 case SyntaxKind::PlusToken:
					return Evaluate(b->Left, s) +  Evaluate(b->Right, s);
				 case SyntaxKind::MinusToken:
					return Evaluate(b->Left, s) -  Evaluate(b->Right, s);
				 case SyntaxKind::StarToken:
					return Evaluate(b->Left, s) *  Evaluate(b->Right, s);
				 case SyntaxKind::SlashToken:
					return Evaluate(b->Left, s) /  Evaluate(b->Right, s);
				}
				throw "Error";
			}
			else
			{
				return 0;
			}

		}

	};

	const char 
		_last[] = { (char)192, (char)196, (char)196, ' ', 0 }, 
		_notLast[] = { (char)195, (char)196, (char)196, ' ', 0 },
		_notLastI[] = { (char)179, ' ', ' ', ' ', 0 };
	
	void PrintNode(Ptr<SyntaxNode> node, string indent = "", bool isLast = true)
	{
		cout << indent;
		const string& marker = isLast ? _last : _notLast;

		cout << marker
				 << ToString(node->Kind);

		if (Ptr<SyntaxToken> token = dynamic_pointer_cast<SyntaxToken>(node))
		{
			if (token->Kind == SyntaxKind::LiteralToken)
				cout << " " << token->Value;
		}
		cout << "\n";
		
		const auto& children = node->GetChildren();
		if(children->size() == 0)
			return;

		indent += isLast ? "    ":_notLastI;
		const auto& lastI = children->size() - 1;
		for (int i = 0; i < children->size(); i++)
			PrintNode(children->at(i), indent, i == lastI);
	}

}

typedef long long ll;

ll pow_ (const int& n, const int& e) {
	ll res = 1LL;
	for (int i = 0; i < e; i++)
		res *= n;
	return res;
}

int main()
{
	using namespace bode;
	using namespace std;

	while (true)
	{
		string text;
		cout << "> ";
		getline(cin, text);

		if (text.size() == 0)
			break;

		Parser parser(text);
		auto syntaxTree = parser.Parse();

		const auto& diagnostics = parser._reporter->Diagnistics;
		PrintNode(syntaxTree->Root);

		if (!diagnostics->size())
		{
			// -arctan(b/a)
			Evaluator evaluator;
			const auto& root = syntaxTree->Root;

			Ptr<BinaryExpressionSyntax> b = dynamic_pointer_cast<BinaryExpressionSyntax>(root);

			if (b && b->OperatorToken->Kind == SyntaxKind::SlashToken)
			{
				vector<double> module;
				for (int i = 0; i < 10; i++) {

					auto num = evaluator.Evaluate(b->Left, pow_(10, i));
					auto den = evaluator.Evaluate(b->Right, pow_(10, i));
					
					auto de2 = den * (-1.0);
					num *= de2;
					den *= de2;

					module.push_back(
						log10(abs(num / den))
					);
				}
				for (auto& e : module)
					cout << e << ' ';
				cout << '\n';
			}
			else 
			{
				vector<double> module;
				for (int i = 0; i < 10; i++) {
					module.push_back(
						log10(abs(evaluator.Evaluate(root, pow_(10, i))))
					);
				}
				for (auto& e : module)
					cout << e << ' ';
				cout << '\n';

				vector<double> phase;
				for (int i = 0; i < 10; i++) {
					const auto& c = evaluator.Evaluate(root, pow_(10, i)); 
					phase.push_back(
						-atan(c.imag() / c.real())
					);
				}
				for (auto& e : phase)
					cout << e << ' ';
				cout << '\n';

			}

		}
		else
		{
			for (const auto& d : (*diagnostics))
				cout << d << "\n";
		}
		
	}

	cin.get();

}