#include "bottom_viewport_controller.hpp"
#include "logger.hpp"

using std::clamp;

void BottomViewportController::_updateConsole()
{
	const auto loggerMessageList = Logger::getMessageList();
	const auto loggerMessageCount = Logger::getMessageCount();

	if(_messageHistory.size() != loggerMessageList.size())
	{
		const auto synchronizationCount = static_cast<int>(loggerMessageList.size() - _messageHistory.size());

		_clearConsole();

		for(int index = (loggerMessageCount - synchronizationCount); index < loggerMessageCount; index++)
		{
			if(_messageQueue.size() == MAX_MESSAGE_COUNT)
			{
				_messageQueue.erase(_messageQueue.begin());
			}

			_messageQueue.push_back(loggerMessageList[index]);
			_messageHistory.push_back(loggerMessageList[index]);
		}

		_fillConsole();
	}

	if(_gui->getBottomViewport()->getWindow("console")->isHovered())
	{
		const auto totalHeight = (static_cast<float>(_messageQueue.size()) * CHAR_SIZE.y);

		if(totalHeight > 2.0f)
		{
			if(_fe3d->input_isMouseScrolled(MouseWheelType::WHEEL_UP))
			{
				_scrollingOffset -= CHAR_SIZE.y;
				_scrollingOffset = clamp(_scrollingOffset, -(totalHeight - 2.0f), 0.0f);

				_clearConsole();
				_fillConsole();
			}
			else if(_fe3d->input_isMouseScrolled(MouseWheelType::WHEEL_DOWN))
			{
				_scrollingOffset += CHAR_SIZE.y;
				_scrollingOffset = clamp(_scrollingOffset, -(totalHeight - 2.0f), 0.0f);

				_clearConsole();
				_fillConsole();
			}
		}
	}
}

void BottomViewportController::_fillConsole()
{
	const auto window = _gui->getBottomViewport()->getWindow("console");
	const auto screen = window->getScreen("main");
	const auto messageCount = static_cast<int>(_messageQueue.size());
	const auto minClipPosition = (window->getPosition() - (window->getSize() * 0.5f));
	const auto maxClipPosition = (window->getPosition() + (window->getSize() * 0.5f));

	for(int index = 0; index < messageCount; index++)
	{
		const auto message = _messageQueue[index];
		const auto timestampText = ("[" + message->getTimestamp() + "]");
		const auto contentText = message->getContent();
		const auto isWarning = (message->getType() == LoggerMessageType::WARNING);
		const auto timestampSize = fvec2((static_cast<float>(timestampText.size()) * CHAR_SIZE.x), CHAR_SIZE.y);
		const auto contentSize = fvec2((static_cast<float>(contentText.size()) * CHAR_SIZE.x), CHAR_SIZE.y);
		const auto y = (-1.0f + _scrollingOffset + (static_cast<float>(messageCount - index - 1) * CHAR_SIZE.y));

		screen->createTextField(("timestamp_" + to_string(index)), fvec2(-1.0f, y), timestampSize, timestampText, TIMESTAMP_COLOR, false);
		screen->createTextField(("content_" + to_string(index)), fvec2((-1.0f + timestampSize.x + CHAR_SIZE.x), y), contentSize, contentText, (isWarning ? WARN_COLOR : INFO_COLOR), false);

		screen->getTextField("timestamp_" + to_string(index))->setMinClipPosition(minClipPosition);
		screen->getTextField("timestamp_" + to_string(index))->setMaxClipPosition(maxClipPosition);
		screen->getTextField("content_" + to_string(index))->setMinClipPosition(minClipPosition);
		screen->getTextField("content_" + to_string(index))->setMaxClipPosition(maxClipPosition);
	}
}

void BottomViewportController::_clearConsole()
{
	const auto screen = _gui->getBottomViewport()->getWindow("console")->getScreen("main");
	const auto messageCount = static_cast<int>(_messageQueue.size());

	for(int index = 0; index < messageCount; index++)
	{
		screen->deleteTextField("timestamp_" + to_string(index));
		screen->deleteTextField("content_" + to_string(index));
	}
}