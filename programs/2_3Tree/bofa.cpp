bool rightDistributionCheck() {
    Node * p = this->parent;
    
    if (p->isFull()) {
        if (this == p->left) {
            if (p->right->isFull()) {
                return true;
            }
        } else if (this == p->middle) {
            if (p->right->isFull()) {
                return true;
            }
        } 
    } else {
        if (this == p->left) {
            if (p->right->isFull()) {
                return true;
            }
        }
    }
    
    return false;
}