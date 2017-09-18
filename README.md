[![license](https://img.shields.io/github/license/StefanoBelli/telegram-bot-api.svg)](https://github.com/StefanoBelli/telegram-bot-api/blob/master/LICENSE)
[![GitHub tag](https://img.shields.io/github/tag/StefanoBelli/telegram-bot-api.svg)](https://github.com/StefanoBelli/telegram-bot-api/tags)
[![Travis](https://img.shields.io/travis/StefanoBelli/telegram-bot-api.svg)](https://travis-ci.org/StefanoBelli/telegram-bot-api)

# telegram-bot-api
C++ Telegram Bot APIs

### Implementation status
May take long time... :)

 * Internal project utils [ directory: *include/tgbot/utils* ]
    [x] HTTPS interface (libcurl wrapper)
    [x] template<typename T> Matrix<T> class template

 * Basic Bot interface [ files: *include/tgbot/bot.h* and *include/tgbot/register_callback.h* ]
    [x] Bot class
    [x] RegisterCallback class
    
 * API Types [ file: *include/tgbot/types.h* ]
    [x] User
	[x]	ChatPhoto
	[x]	MessageEntity
	[x]	Audio
	[x]	PhotoSize
	[x]	Document
	[x]	Voice
	[x]	Contact
	[x]	Location
	[x]	Animation
	[x]	Venue
	[x]	VideoNote
	[x]	MaskPosition
	[x]	Sticker
	[ ]	StickerSet
	[x]	Video
	[x]	Invoice
	[x]	ShippingAddress
	[ ]	OrderInfo
	[x]	SuccessfulPayment
	[x]	Game
	[x]	Chat
	[ ]	Message
	[x]	InlineQuery
	[x]	ChosenInlineResult
	[x]	CallbackQuery
	[x]	ShippingQuery
	[x]	PreCheckoutQuery
	[x]	Update
	[ ]	ResponseParameters
	[ ]	ForceReply
	[ ]	File
	[ ]	UserProfilePhotos
	[ ]	KeyboardButton
	[ ]	ReplyKeyboardMarkup
	[ ]	ReplyKeyboardRemove
	[ ]	InlineKeyboardButton
	[ ]	InlineKeyboardMarkup
	[ ]	ChatMember
	
 * API Methods and input types [ directory: *include/tgbot/methods* ]
    Implementation pending
