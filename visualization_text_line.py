import matplotlib.pyplot as plt
import itertools

def draw_curve(filename):
    # Open the file
    with open(filename, 'r') as f:
        # Read the sequence from the first line
        sequence = f.readline().strip()
        
        # Read the pairs from the following lines
        pairs = []
        for line in f:
            pair = tuple(map(int, line.strip().split(',')))
            pairs.append(pair)
    
   # Calculate plot width based on sequence length
    plot_width = max(10, len(sequence) / 5)  # Adjust the divisor as needed
    
    # Initialize plot with dynamic size
    fig, ax = plt.subplots(figsize=(plot_width, 10))  # Height is still 10
    
    # Plot points
    for i, nucleotide in enumerate(sequence):
        plt.scatter(i, 0, color='blue')  # Plot points along the x-axis
        plt.text(i, -0.02, nucleotide, ha='center', va='center')  # Label points with their nucleotide
    
    colors = itertools.cycle(['b', 'g', 'r', 'c', 'm', 'y', 'k'])
    
    # Plot curves for each pair
    for pair in pairs:
        idx1, idx2 = pair
        x1, x2 = idx1, idx2
        y1, y2 = 0, 0
        plt.plot([x1, x1, x2], [y1, 0.5, y2], color=next(colors))  # Plot curves between points
        plt.pause(1)
    
    # Set labels and title
    plt.xlabel('Index')
    plt.title('Curves between pairs of points')
    
    # Remove y-axis
    plt.gca().axes.get_yaxis().set_visible(False)
    plt.xticks([])
    
    # Show plot
    plt.grid(True)
    plt.savefig('plot_line.png', dpi=300)
    plt.show()

# Example usage
draw_curve('output.txt')