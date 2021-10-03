import os, discord, serial, asyncio
health, hunger, old_emoji = 10, 10, None
client = discord.Client()
cat_emojis,dog_emojis,Names = ["😻","😹","😽","😸","😺","😾","😼","😿","🙀"],["🐶","🦮","🐕‍🦺","🐕"], ["cool","joy","kiss","happy","neutral","angry","smirk","sad"]

#MAX HUNGER = 10
#MAX HEALTH = 10

#Send output of cat state:
# hunger, health
async def update_emoji():
  global health, hunger, old_emoji
  emoji = str(int(health / 3.4)*3 + int(hunger / 3.4) + 1)
  if old_emoji != emoji:
    old_emoji = emoji
    print(emoji)
  print(str(int(10-health)) + "," + str(int(10-hunger)))
@client.event
async def on_ready():
  global health, hunger
  print(f'{client.user} has connected to Discord!')
  
  #Decrease Hunger over time
  while True:
    await asyncio.sleep(10)
    hunger += 1
    if hunger > 10:
      hunger = 10
    await update_emoji()


@client.event
async def on_message(message):
  global health, hunger
  if message.author != client.user:

    hunger -= 1
    if hunger < 0:
      hunger = 0

    #check emoji input:
    #increase health for cat emoji
    #decrease health for dog
    emoji = None
    for i in message.content:
      if i in cat_emojis:
        emoji = cat_emojis.index(i)
        health -= 1
        if health < 0:
          health = 0
      elif i in dog_emojis:
        health += 1
        if health > 10: 
          health = 10

    #DISCORD ONLY: send cat gif for cat emoji
    await update_emoji()
    if emoji != None:
      await message.channel.send(file=discord.File(Names[emoji] + ".gif")) #send appropriate cat gif
    elif str(message.content)[0:6] == "!clear":
      [await i.delete() async for i in message.channel.history(limit=200)] #not cat = ignore
client.run(os.getenv('BOT_TOKEN'))