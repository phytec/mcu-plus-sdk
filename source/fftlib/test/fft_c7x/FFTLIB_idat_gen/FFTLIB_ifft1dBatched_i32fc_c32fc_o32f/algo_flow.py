import numpy as np

# Size of input complex sequence
# N = 1024
# mode = 0 -> full spectrum input including the conjugate symmetric part
# mode = 1 -> half spectrum input does not include conjugate symmetric part


def algo_flow(numChannels, N, mode):

    gInput = np.round(100 * np.random.rand(numChannels, N), 6)
    G = np.round(np.fft.fft(gInput), 6)
    print(np.round(G), 2)

    ## Generate post-processing twiddle vectors
    pi = np.pi
    k = np.arange(0, int(N / 2), 1)
    tw = np.cos(2 * pi * k / (N)) - np.sin(2 * pi * k / (N)) * 1j
    A = np.round(0.5 * (1 - 1j * tw), 6)
    B = np.round(0.5 * (1 + 1j * tw), 6)
    A = np.conjugate(A)
    B = np.conjugate(B)

    G1 = G[:, 0 : int(N / 2)]
    # G2 = np.concatenate(
    #     (G[int(N / 2)], np.conjugate(np.flip(G1)[:-1])), axis=None
    # )
    G2 = G[:, int(N / 2) :]
    X = np.round(G1 * A + G2 * B, 6)

    ## Perform N/2-point IFFT
    x = np.round(np.fft.ifft(X), 6)

    g = np.zeros((numChannels, N))
    g[:, 0::2] = x.real
    g[:, 1::2] = x.imag

    ## Generate N-point FFT from input real sequence for reference
    # g_IFFT = np.round(np.fft.ifft(G), 6)

    ## Compare N-point FFT reference to output generated via N/2-point FFT
    # print(np.allclose(g, gInput, atol=1e-1))
    print(np.allclose(g, gInput, rtol=1e-1))
    # print(np.round(X, 3))
    # print(np.round(G1 * A, 3))
    # print(np.round(G2 * B, 3))
    # print(g)
    # print(gInput)

    # print(np.round(A, 3))
    # print(np.round(B, 3))

    return [G, g]
