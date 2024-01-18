import gym

# Gym ortamını oluştur
env = gym.make('CartPole-v1')

# Ortamı başlat
observation = env.reset()

# Episode başlangıcında render() fonksiyonunu çağırma
env.render()

done = False
while not done:
    # Rastgele bir eylem seçme (örneğin, CartPole ortamında 0 veya 1)
    action = env.action_space.sample()

    # Seçilen eylemi uygulayarak bir adım yapma
    observation, reward, done, _ = env.step(action)

    # Her adımda render() fonksiyonunu çağırma
    env.render()

# Ortamı kapatma (çok önemli)
env.close()